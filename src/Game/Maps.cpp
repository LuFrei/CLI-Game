#include "Maps.h"

MapData title ={
    60, 28,
"\
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
                     #                #                     \
                     #   s        e   #                     \
                     ##################                     \
                                                            \
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


MapData theRoom0 = {
    18, 9,
"\
##################\
#                #\
#                #\
#                #\
#                #\
#                #\
#                #\
#   e        s   #\
##################"
};

MapData theRoom1 = {
    18, 9,
"\
##################\
#                #\
#                #\
#                #\
#                #\
#                #\
#                #\
#   s    #    e  #\
##################"
};

MapData theRoom2 = {
    18, 9,
"\
##################\
#        *       #\
#        *       #\
#        *       #\
#        e       #\
#        *       #\
#        *       #\
#        #    s  #\
##################"
};

MapData theRoom3 = {
    18, 9,
"\
###   ############\
# #***#          #\
#                #\
#                #\
#        s       #\
#                #\
#                #\
#        #    e  #\
##################"
};

MapData theRoom4 = {
    18, 9,
"\
###   ############\
# #***#          #\
#            e   #\
#                #\
#                #\
#                #\
##########       #\
         #    s  #\
         #########"
};

MapData theRoom5 = {
    18, 9,
"\
###   ############\
# #*e*#          #\
#            s   #\
#                #\
#                #\
##########       #\
         #       #\
         #       #\
         #########"
};

MapData easyDoesIt = {
    8, 15,
"\
########\
#      #\
#  ### #\
#  #   #\
#e*#   #\
   # ###\
   #   #\
   #   #\
   ### #\
   #   #\
   #   #\
   # ###\
   # s #\
   #   #\
   #####"
};

MapData tallJumps = {
    31, 13,
"\
#s #          #################\
#  #               ##         #\
#  #               ##   #  e  #\
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


MapData ohChute = {
    4, 9,
"\
#s #\
#  #\
#  #\
#  #\
#  #\
#  #\
#  #\
#  #\
#e*#"
};

MapData map01 ={
    30, 30,
"\
##############################\
#                            #\
#                          e #\
#     #       ### ### ## #####\
#     #    ####              #\
#     #       #           #  #\
#  #  #  #    #           #  #\
#     #       #           #  #\
#             #   ######  #  #\
#   #         ##  #       #  #\
#             #   #       #  #\
#             #   # s #   #  #\
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

Maps* Maps::_instance;
const std::vector<MapData> Maps::list = {
        title,
        theRoom0,
        theRoom1,
        theRoom2,
        theRoom3,
        theRoom4,
        theRoom5,
        easyDoesIt,
        ohChute,
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