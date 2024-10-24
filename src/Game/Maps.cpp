#include "Maps.h"

// 27 max depth (including offsets)
// want to reserve bottom rows for messages

// 60 x 30
MapData titleMap ={
    60, 28,
    0, 1,"\
                                                            \
                                                            \
                                                            \
                                                            \
                                                            \
                                                            \
                                                            \
         ###  #           #            #   ###              \
         # #  #           #            #    #               \
         #### # #### #### #  # #### ####    #  # ##         \
         #  # # #  # #    ###  ##   #  #    #  ## #         \
         #  # # #  # #    #  # #    #  #    #  #  #         \
         #### # #### #### #  # #### ####   ### #  #         \
                                                            \
                                                            \
                                                            \
                     ##################                     \
                     #                #                     \
                     #                #                     \
                     #                #                     \
                     #                #                     \
                     #                #                     \
                     #   s        *   #                     \
                     ##################                     \
                                                            \
                                                            \
                                                            \
                                                            \
                                                            \
                                                            \
                                                            \
                                                            "
};
//       1         2         3         4         5         6 


// 30 x 30
MapData map01 ={
    30, 30,
    0, 0, "\
##############################\
#                            #\
#                          * #\
#     #       ### ### ## #####\
#     #    ####              #\
#     #       #           #  #\
#  #  #  #    #           #  #\
#     #       #           #  #\
#             #   ######  #  #\
#   #         ##  #       #  #\
#             #   #       #  #\
#             #   #   #   #  #\
#  ##      #  #  ######   #  #\
#          #  #           #  #\
#      #####  #           #  #\
#            ###          #  #\
#          ################  #\
#                 #          #\
#        #        #          #\
#  ###            #          #\
#                 # ###      #\
#                            #\
#    ##                      #\
#                      ###   #\
#                 #          #\
#  ###    #   #####          #\
#             #           ####\
#             #              #\
#                            #\
##############################"
};

// 31 x 13
MapData tallJumps = {
    31, 13,
    18, 12,"\
#  #          #################\
#  #               ##         #\
#  #               ##   #  *  #\
#  #          ###  ##   #     #\
#             ###  ##   #######\
#         ### ###  ####       #\
#             ###  ####       #\
#             ###  ####       #\
#      ###    ###  #########  #\
#             ###             #\
#             ###             #\
###############################\
###############################"
};

MapData babyHops = {
    18, 8,
    21, 17,"\
##################\
#                #\
#                #\
#                #\
#   *   #        #\
#       #        #\
#       #        #\
##################"
};

MapData easyDoesIt = {
    8, 15,
    22, 10,"\
########\
#      #\
#  ### #\
#  #   #\
#**#   #\
   # ###\
   #   #\
   #   #\
   ### #\
   #   #\
   #   #\
   # ###\
   #   #\
   #   #\
   #####"
};


Maps* Maps::_instance;
const MapData Maps::list[MAX_LEVELS]= {
        titleMap,
        babyHops,
        easyDoesIt,
        tallJumps,
        map01
    };

Maps::Maps(){
    try{
        if(_instance != nullptr){
            throw "Only one Maps is allowed.";
        }
    } catch (std::string msg) {}

    _instance = this;
}