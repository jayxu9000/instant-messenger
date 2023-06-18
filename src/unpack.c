#include <stdlib.h>
#include <string.h>

#include "serialize.h"

/* Unpack the given packet into the buffer unpacked.  You can assume
 * that packed points to a packet buffer large enough to hold the
 * packet described therein, but you cannot assume that the packet is
 * otherwise valid.  You can assume that unpacked points to a character
 * buffer large enough to store the unpacked packet, if it is a valid
 * packet.
 *
 * Returns the packet type that was unpacked, or -1 if it is invalid.
 */
int unpack(char *unpacked, void *packed) {
    int type = *(int *) packed;
    if (type == MESSAGE) {
        packed += sizeof(int);

        for (int i = 0; i != NAME_SIZE ; i++) {
            if (*(char *) packed != '\0') {
                char ubit = *(char *) packed;
                *(char *) unpacked = ubit;
                packed += sizeof(char);
                unpacked += sizeof(char);
            }
            else {
                packed += sizeof(char);
            }
        }

        *(char *) unpacked = ':';
        unpacked += sizeof(char);
        *(char *) unpacked = ' ';
        unpacked += sizeof(char);

        size_t message_length = *(size_t *) packed;
        packed += sizeof(size_t);
        packed += sizeof(size_t);

        for (size_t i = 0; i != message_length; i++) {
            char data = *(char *) packed;
            *(char *) unpacked = data;
            packed += sizeof(char);
            unpacked += sizeof(char);
        }

        *(char *) unpacked = '\0';
        return MESSAGE;
    }
    else if (type == STATUS) {
        packed += sizeof(int);

        for (int i = 0; i != NAME_SIZE ; i++) {
            if (*(char *) packed != '\0') {
                char ubit = *(char *) packed;
                *(char *) unpacked = ubit;
                packed += sizeof(char);
                unpacked += sizeof(char);
            }
            else {
                packed += sizeof(char);
            }
        }

        size_t status_length = *(size_t *) packed;
        packed += sizeof(size_t);
        packed += sizeof(size_t);

        *(char *) unpacked = ' ';
        unpacked += sizeof(char);

        size_t index = 0;
        for (size_t i = 0; i != status_length; i++) {
            if (*(char *) packed == ' ') {
                index += 1;
                packed += sizeof(char);
            }
            else {
                break;
            }
        }

        for (size_t i = index; i != status_length; i++) {
            char data = *(char *) packed;
            *(char *) unpacked = data;
            packed += sizeof(char);
            unpacked += sizeof(char);
        }

        *(char *) unpacked = '\0';
        return STATUS;
    }
    else if (type == LABELED) {
        packed += sizeof(int);

       for (int i = 0; i != NAME_SIZE ; i++) {
            if (*(char *) packed != '\0') {
                char ubit = *(char *) packed;
                *(char *) unpacked = ubit;
                packed += sizeof(char);
                unpacked += sizeof(char);
            }
            else {
                packed += sizeof(char);
            }
        }

       *(char *) unpacked = ':';
        unpacked += sizeof(char);
        *(char *) unpacked = ' ';
        unpacked += sizeof(char);
        *(char *) unpacked = '@';
        unpacked += sizeof(char);

        size_t message_length = *(size_t *) packed;

        packed += sizeof(size_t);
        size_t target_length = *(size_t *) packed;
        packed += sizeof(size_t);
        packed += sizeof(size_t);

        char message[message_length];
        for (size_t i = 0; i != message_length; i++) {
            message[i] = *(char *) packed;
            packed += sizeof(char);
        }

        char target[target_length];
        for (size_t i = 0; i != target_length; i++) {
            target[i] = *(char *) packed;
            packed += sizeof(char);
        }

        for (size_t i = 0; i != target_length; i++) {
            *(char *) unpacked = target[i];
            unpacked += sizeof(char);
        }

        *(char *) unpacked = ' ';
        unpacked += sizeof(char);

        for (size_t i = 0; i != message_length; i++) {
            *(char *) unpacked = message[i];
            unpacked += sizeof(char);
        }

        *(char *) unpacked = '\0';
        return LABELED;
        }
    else {
        return -1;
    }
}

/* Unpack the given packed packet into the given statistics structure.
 * You can assume that packed points to a packet buffer large enough to
 * hold the statistics packet, but you cannot assume that it is
 * otherwise valid.  You can assume that statistics points to a
 * statistics structure.
 *
 * Returns the packet type that was unpacked, or -1 if it is invalid.
 */
int unpack_statistics(struct statistics *statistics, void *packed) {
    int type = *(int *) packed;
    if (type == STATISTICS) {
        packed += sizeof(int);

        memcpy(statistics -> sender, (char *) packed, NAME_SIZE);

        statistics -> messages_count = *(int *) (packed + NAME_SIZE + NAME_SIZE + sizeof(int)
                                                 + sizeof(long) + sizeof(long));

        memcpy(statistics -> most_active, (char *) (packed + NAME_SIZE), NAME_SIZE);

        statistics -> most_active_count = *(int *) (packed + NAME_SIZE + NAME_SIZE);

        statistics -> invalid_count = *(long *) (packed + NAME_SIZE + NAME_SIZE + sizeof(int));

        statistics -> refresh_count = *(long *) (packed + NAME_SIZE + NAME_SIZE + sizeof(int) + sizeof(long));

        return STATISTICS;
        }
    else {
        return -1;
    }
}
