#include <stdlib.h>
#include <string.h>

#include "serialize.h"

/* Pack the user input provided in input into the appropriate message
 * type in the space provided by packed.  You can assume that input is a
 * NUL-terminated string, and that packed is a buffer of size
 * PACKET_SIZE.
 *
 * Returns the packet type for valid input, or -1 for invalid input.
 */
int pack(void *packed, char *input) {

    int input_type;

    if (input[0] == '@') {
        input_type = LABELED;
    }
    else if (input[0] == '/' &&
             input[1] == 'm' &&
             input[2] == 'e') {
        input_type = STATUS;
    }
    else if (input[0] == '/' &&
             input[1] == 's' &&
             input[2] == 't' &&
             input[3] == 'a' &&
             input[4] == 't' &&
             input[5] == 's' ) {
        input_type = STATISTICS;
    }
    else {
        input_type = MESSAGE;
    }

    if (input_type == MESSAGE) {

        int space_invalid = 0;
        for (int i = 0; input[i] != '\0'; i++) {
            if (input[i] == ' ') {
                space_invalid += 0;
            }
            else {
                space_invalid += 1;
            }
        }

        if (space_invalid == 0) {
            return -1;
        }

        *(int *) packed = MESSAGE;
        packed += sizeof(int);

        *(char *) packed = 'y';
        packed += sizeof(char);
        *(char *) packed = 'u';
        packed += sizeof(char);
        *(char *) packed = 'a';
        packed += sizeof(char);
        *(char *) packed = 'n';
        packed += sizeof(char);
        *(char *) packed = 'j';
        packed += sizeof(char);
        *(char *) packed = 'i';
        packed += sizeof(char);
        *(char *) packed = 'e';
        packed += sizeof(char);
        *(char *) packed = 'x';
        packed += sizeof(char);

    for (size_t i = 0; i != 8; i++) {
        *(char *) packed = '\0';
        packed += sizeof(char);
    }

        size_t message_length = 0;
        for (int i = 0; input[i] != '\0'; i++) {
            message_length++;
        }
        *(size_t *) packed = message_length;
        packed += sizeof(size_t);

        size_t terminating_zero = 0;
        *(size_t *) packed = terminating_zero;
        packed += sizeof(size_t);

        for (int i = 0; input[i] != '\0'; i++) {
            *(char *) packed = input[i];
            packed += sizeof(char);
        }

        return MESSAGE;
    }

    else if (input_type == STATUS) {

        if (input[3] != ' ') {
            return -1;
        }

        int space_invalid = 0;
        for (int i = 4; input[i] != '\0'; i++) {
            if (input[i] == ' ') {
                space_invalid += 0;
            }
            else {
                space_invalid += 1;
            }
        }

        if (space_invalid == 0) {
            return -1;
        }

        *(int *) packed = STATUS;
        packed += sizeof(int);

        *(char *) packed = 'y';
        packed += sizeof(char);
        *(char *) packed = 'u';
        packed += sizeof(char);
        *(char *) packed = 'a';
        packed += sizeof(char);
        *(char *) packed = 'n';
        packed += sizeof(char);
        *(char *) packed = 'j';
        packed += sizeof(char);
        *(char *) packed = 'i';
        packed += sizeof(char);
        *(char *) packed = 'e';
        packed += sizeof(char);
        *(char *) packed = 'x';
        packed += sizeof(char);

        for (size_t i = 0; i != 8; i++) {
            *(char *) packed = '\0';
            packed += sizeof(char);
        }

        size_t status_length = 0;
        for (int i = 4; input[i] != '\0'; i++) {
            status_length++;
        }
        *(size_t *) packed = status_length;
        packed += sizeof(size_t);

        size_t terminating_zero = 0;
        *(size_t *) packed = terminating_zero;
        packed += sizeof(size_t);

        for (int i = 4; input[i] != '\0'; i++) {
            *(char *) packed = input[i];
            packed += sizeof(char);
        }

        return STATUS;
    }

    else if (input_type == LABELED) {

        size_t target_length = 0;
        for (size_t i = 1; input[i] != ' '; i++) {
            target_length++;
        }

        int space_invalid = 0;
        for (int i = target_length + 2; input[i] != '\0'; i++) {
            if (input[i] == ' ') {
                space_invalid += 0;
            }
            else {
                space_invalid += 1;
            }
        }

        if (space_invalid == 0) {
            return -1;
        }

        *(int *) packed = LABELED;
        packed += sizeof(int);

        *(char *) packed = 'y';
        packed += sizeof(char);
        *(char *) packed = 'u';
        packed += sizeof(char);
        *(char *) packed = 'a';
        packed += sizeof(char);
        *(char *) packed = 'n';
        packed += sizeof(char);
        *(char *) packed = 'j';
        packed += sizeof(char);
        *(char *) packed = 'i';
        packed += sizeof(char);
        *(char *) packed = 'e';
        packed += sizeof(char);
        *(char *) packed = 'x';
        packed += sizeof(char);

        for (size_t i = 0; i != 8; i++) {
            *(char *) packed = '\0';
            packed += sizeof(char);
        }

        size_t message_length = 0;
        for (size_t i = target_length + 2; input[i] != '\0'; i++) {
            message_length++;
        }
        *(size_t *) packed = message_length;
        packed += sizeof(size_t);
        *(size_t *) packed = target_length;
        packed += sizeof(size_t);

        size_t terminating_zero = 0;
        *(size_t *) packed = terminating_zero;
        packed += sizeof(size_t);

        for (size_t i = 0; i != message_length; i++) {
            *(char *) packed = input[i + target_length + 2];
            packed += sizeof(char);
        }

        for (size_t k = 0; k != target_length; k++) {
            *(char *) packed = input[k + 1];
            packed += sizeof(char);
        }

        return LABELED;
    }
    else if (input_type == STATISTICS) {

        if (input[6] != '\0') {
            return -1;
        }

        *(int *) packed = STATISTICS;
        packed += sizeof(int);

        *(char *) packed = 'y';
        packed += sizeof(char);
        *(char *) packed = 'u';
        packed += sizeof(char);
        *(char *) packed = 'a';
        packed += sizeof(char);
        *(char *) packed = 'n';
        packed += sizeof(char);
        *(char *) packed = 'j';
        packed += sizeof(char);
        *(char *) packed = 'i';
        packed += sizeof(char);
        *(char *) packed = 'e';
        packed += sizeof(char);
        *(char *) packed = 'x';
        packed += sizeof(char);

        for (size_t i = 0; i != 8; i++) {
            *(char *) packed = '\0';
            packed += sizeof(char);
        }

        return STATISTICS;
    }
    else {
        return -1;
    }
 }

/* Create a refresh packet for the given message ID.  You can assume
 * that packed is a buffer of size PACKET_SIZE.
 *
 * You should start by implementing this method!
 *
 * Returns the packet type.
 */
int pack_refresh(void *packed, int message_id) {

    *(int *) packed = REFRESH;
    packed += sizeof(int);

    *(char *) packed = 'y';
    packed += sizeof(char);
    *(char *) packed = 'u';
    packed += sizeof(char);
    *(char *) packed = 'a';
    packed += sizeof(char);
    *(char *) packed = 'n';
    packed += sizeof(char);
    *(char *) packed = 'j';
    packed += sizeof(char);
    *(char *) packed = 'i';
    packed += sizeof(char);
    *(char *) packed = 'e';
    packed += sizeof(char);
    *(char *) packed = 'x';
    packed += sizeof(char);

    for (int i = 0; i != 8; i++) {
        *(char *) packed = '\0';
        packed += sizeof(char);
    }

    *(int *) packed = message_id;

    return REFRESH;
}
