#include <fcntl.h>
#include <linux/input.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

struct shortcut {
    char name[20];
    int keycode;
};

static const struct shortcut shortcuts[] = {
    {"PE+", 0x31}, {"CAP+P", 0x10}, {"CUSTOM", 0x45}
};

int main() {
    int fd = open("/dev/input/by-path/platform-i8042-serio-0-event-kbd", O_RDONLY);
    if (fd < 0) {
        perror("Error opening keyboard device");
        return 1;
    }

    printf("Available shortcuts:\n");
    for (int i = 0; i < sizeof(shortcuts) / sizeof(struct shortcut); i++) {
        printf("%s\n", shortcuts[i].name);
    }

    struct input_event ev;
    while (read(fd, &ev, sizeof(struct input_event))) {
        switch (ev.type) {
            case INPUT_EVENT_KEY:
                switch (ev.code) {
                    case KEY_PRESSED:
                    case KEY_REPEATED:
                    case KEY_RELEASED:
                        for (int i = 0; i < sizeof(shortcuts) / sizeof(struct shortcut); i++) {
                            if (ev.value == shortcuts[i].keycode) {
                                printf("EXECUTED SHORTCUT: %s\n", shortcuts[i].name);
                            }
                        }
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }

    close(fd);
    return 0;
}
