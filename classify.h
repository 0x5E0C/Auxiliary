#ifndef CLASSIFY_H
#define CLASSIFY_H

#include <QObject>
#include "config.h"
#include "yuhun.h"
#include "juexing.h"
#include "yuling.h"
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
    QString resolution;
    int winheight;
    int matchtarget;
    QString floortext;
    bool magatama30;
    bool strength30;
    bool gold2w;
    bool gold3w;
    bool autoprepare;
    bool addoperations;
    bool failstop;
    bool stopwhenlimit;
    qint8 jiejiepropcount;
    bool popupstop;
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
        struct prepare_pos
        {
            double xpos;
            double ypos;
        }prepare_pos;
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
    struct cooperation
    {
        struct accept
        {
            double xpos;
            double ypos;
        } accept;
        struct refuse
        {
            double xpos;
            double ypos;
        } refuse;
    }cooperation;
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
