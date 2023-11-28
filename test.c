#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <string.h>

#define MAX_SHORTCUTS 3
#define MAX_SHORTCUT_LENGTH 6

// Define the custom shortcuts
char shortcuts[MAX_SHORTCUTS][MAX_SHORTCUT_LENGTH] = {
    "P+E",
    "C+A+P",
    "F1+F2"
};

// Define the messages for the custom shortcuts
char shortcut_messages[MAX_SHORTCUTS][50] = {
    "I passed the Exam!",
    "Get some cappuccino!",
    "This is a custom shortcut!"
};

// Function to check if a shortcut is pressed
int is_shortcut_pressed(char *shortcut, int shortcut_length, int *keys, int num_keys) {
    int i, j;
    int shortcut_keys[MAX_SHORTCUT_LENGTH];
    int shortcut_num_keys = 0;

    // Convert the shortcut string to an array of key codes
    for (i = 0; i < shortcut_length; i++) {
        if (shortcut[i] == '+') {
            continue;
        }
        shortcut_keys[shortcut_num_keys++] = shortcut[i];
    }

    // Check if the shortcut is pressed
    if (shortcut_num_keys == num_keys) {
        for (i = 0; i < num_keys; i++) {
            for (j = 0; j < shortcut_num_keys; j++) {
                if (keys[i] == shortcut_keys[j]) {
                    break;
                }
            }
            if (j == shortcut_num_keys) {
                break;
            }
        }
        if (i == num_keys) {
            return 1;
        }
    }

    return 0;
}

int main() {
    int fd;
    struct input_event ev;
    int shortcut_pressed;
    int keys_pressed[6];
    int num_keys_pressed = 0;
    int i, j;

    // Open the keyboard device file
    fd = open("/dev/input/by-path/platform-i8042-serio-0-event-kbd", O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    // Open the output file for appending
    FILE *f = fopen("ex1.txt", "a");
    if (f == NULL) {
        perror("fopen");
        exit(1);
    }

    // Print the available shortcuts
    printf("Available shortcuts:\n");
    for (i = 0; i < MAX_SHORTCUTS; i++) {
        printf("%s -> %s\n", shortcuts[i], shortcut_messages[i]);
    }

    // Read keyboard events and handle shortcuts
    while (1) {
        if (read(fd, &ev, sizeof(ev)) < sizeof(ev)) {
            perror("read");
            exit(1);
        }

        // Handle only PRESSED, REPEATED, and RELEASED events
        if (ev.type == EV_KEY && (ev.value == 0 || ev.value == 1 || ev.value == 2)) {
            // Handle shortcuts
            shortcut_pressed = 0;
            if (num_keys_pressed > 0 && ev.value == 0) {
                for (i = 0; i < MAX_SHORTCUTS; i++) {
                    if (is_shortcut_pressed(shortcuts[i], strlen(shortcuts[i]), keys_pressed, num_keys_pressed)) {
                        fprintf(f, "%s\n", shortcut_messages[i]);
                        shortcut_pressed = 1;
                        break;
                    }
                }
            }

            // Handle output events
            if (!shortcut_pressed) {
                if (ev.value == 0) {
                    for (i = 0; i < num_keys_pressed; i++) {
                        if (keys_pressed[i] == ev.code) {
                            for (j = i; j < num_keys_pressed - 1; j++) {
                                keys_pressed[j] = keys_pressed[j + 1];
                            }
                            num_keys_pressed--;
                            break;
                        }
                    }
                    fprintf(f, "RELEASED 0x%04x (%d)\n", ev.code, ev.code);
                } else if (ev.value == 1 || ev.value == 2) {
                    keys_pressed[num_keys_pressed++] = ev.code;
                    fprintf(f, "PRESSED 0x%04x (%d)\n", ev.code, ev.code);
                }
            }

            // Terminate the program on E+X
            if (num_keys_pressed == 2 && keys_pressed[0] == 18 && keys_pressed[1] == 45) {
                fclose(f);
                close(fd);
                exit(0);
            }

            fflush(f);
        }
    }

    return 0;
}
