#ifndef CLASSIFY_H
#define CLASSIFY_H

#include <QObject>
#include "config.h"
#include "yuhun.h"
#include "prompt.h"

extern bool *threadflaglist[MAX_PROCESS_COUNT];
extern int process_count;
extern struct guichoose{
    int challengetype;
    int mfloor;
    bool isteam;
    int person;
    int propcount;
    int challengetimes;
    bool addoperations;
    QString resolution;
    int winheight;
    int matchtarget;
    QString floortext;
} guiInfo;

extern struct pos
{
    struct common
    {
        struct single_challenge_pos
        {
            double xpos;
            double ypos;
        } single_challenge_pos;
        struct team_challenge_pos
        {
            double xpos;
            double ypos;
        } team_challenge_pos;
        struct friend_pos
        {
            double xpos;
            double ypos;
        } friend_pos;
        struct chat_pos
        {
            double xpos;
            double ypos;
        } chat_pos;
        struct finish_pos
        {
            double xpos;
            double ypos;
        } finish_pos;
    }common;
} posInfo;

class classify : public QObject
{
    Q_OBJECT
public:
    explicit classify();
    void startTask();
    void startSingleModeMatch();
    void startTeamModeMatch();
    void recordKeyPos();
    void scanProcess();

private:
    HWND handle_list[MAX_PROCESS_COUNT];

};

#endif // CLASSIFY_H
