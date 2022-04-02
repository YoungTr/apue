//
// Created by YoungTr on 2022/4/1.
//

#ifndef APUE_SHMDATA_H
#define APUE_SHMDATA_H

#define TEXT_SZ 2048

struct shared_use_st {
    int written;
    char text[TEXT_SZ];
};

#endif //APUE_SHMDATA_H
