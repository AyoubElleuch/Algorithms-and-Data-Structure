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
    int i
