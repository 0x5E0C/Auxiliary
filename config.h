#ifndef CONFIG_H
#define CONFIG_H

#include <QString>
#include <QDebug>
#include <Windows.h>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#define desktopID           65552

#define ERR                 0
#define INFO                1

#define BASE_TIME           100
#define CLICK_TIME_INTERBAL 200
#define SAMPLE_TIME         200

#define MAX_PROCESS_COUNT   8

#define NO_KILL_PROCESS     0
#define KILL_PROCESS        1

#define C_YUHUN             0
#define C_JUEXING           1
#define C_YULING            2

#define TIMES_TYPE          0
#define PROPS_TYPE          1
#define JPROPS_TYPE         2

#define STRENGTH_4          4
#define STRENGTH_6          6
#define STRENGTH_8          8
#define STRENGTH_9          9
#define STRENGTH_12         12

#define PROP_TAN            -1
#define PROP_CHEN           -2
#define PROP_CHI            -3
#define PROP_YULING         -4

#define FIGHT_VICTORY       2
#define FIGHT_FAIL          3

#define NO_MATCH            0
#define GOOD_MATCH          1

enum floor
{
    not_choose,
    floor_1_10,
    floor_11,
    floor_tan,
    floor_chen,
    floor_chi,
    floor_rlzy1,
    floor_rlzy2,
    floor_rlzy3
};

enum mode
{
    single_mode,
    team_mode,
    yyh_mode,
    yuling_mode,
    prepare_mode,
    fight_mode
};

enum settingindex
{
    index_resolution,
    index_magatama30,
    index_strength30,
    index_gold2w,
    index_gold3w,
    index_autoprepare,
    index_otheroperations,
    index_failstop,
    index_stopwhenlimit,
    index_jiejiepropcount,
    index_popupwhenstop,
    index_end
};

enum cooperation
{
    cooperation_accept,
    cooperation_refuse,
    no_find
};

const QString title="阴阳师-网易游戏";

#endif // CONFIG_H
