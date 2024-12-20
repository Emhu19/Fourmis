#include "animation.h"

const char *fourmi[] = {
    "                                                  ",
    " ",
    "                   %##                                                                              ",
    "                    %%##                       *+*******                                            ",
    "                      %%#**                **####     ###                                           ",
    "                         %%#**           #*##                                                       ",
    "                            ###+        ##                                                          ",
    "                               %##    #%                                                            ",
    "                                 %%*+*####**#                                                       ",
    "                              %#%##*###*+++=+#*          #**#                                       ",
    "                             ###%#%@%#+*%######*+       #### #*                                     ",
    "                            =+#%#%%*++**+===*###*+     *##** *#*                                    ",
    "                        ##**###%%####+--===-=#%##*     ##**   *##*                                  ",
    "                     ***%%+*##+%%%%%%%**%*==+*%%%*%   *###*    ****                                 ",
    "                   **#%     ++++###%%@%%@%***#@@#*++*#*##*+      ***                                ",
    "                  #*%           +++++%@@@@@%%@@%*++***#**+        ***##%*##                         ",
    "                *#%                **++***##%%%%#+=+++####+       *#%##** *#**                      ",
    "              %*#%                    %##%##* *%#*##*+*#****    -*%##*+    ***** +                  ",
    "             %*%%                             ##%@@@@@%#%%**   *%#**+        **#**                  ",
    "                                       %***    #%%%%@@@@@@%*  ##*++          # *****        #       ",
    "                                    #%*%@%%#*+ ##%@%%@@@%@%***#+==    #######     *######*###*#     ",
    "                                  -*#* *=+#%%%*%%#%%%%%%%@%##%%%###*+%%%#######                     ",
    "                                 =**+    ##%%@@@%##%%%*#%@@@@%#*##%%#*#%*+    %%#                   ",
    "                             %%*=*++               #%@%#%@@%**-:.=*%%%*+#      ##*                  ",
    "                              #+****               %%@#*%@@%#*+-.:=*%@@#*+=    ****+                ",
    "                   %##%%    ##**   .            *#@@%%#*#@@@@@%#++*+*#@%%*==   %##*++#%             ",
    "                       %%%#%##                @@@@@#+*%@@@@@@@%%%+::+%%@%##*   %  +*#               ",
    "                                              %%@@@@  ++#%@@@@@@@%***%%%@#++*     %****             ",
    "                                            @@%       +##*%@@@@@@@@@%%%%%%*+++       *#%            ",
    "                                           %%%         -+#%@@@@@@@@@@@@@%%**++         ####         ",
    "                                          #%%#          +*##%@@@@@@@@@@@@@#*+*           %%#%%%     ",
    "                                         ##%**           =***#%@@@@@@@@@@@#*+*               ##%@   ",
    "                                        **###             **+++*#@@@@@@@@%#*++                      ",
    "                                        ###                  +==+**##%%%%#**                        ",
    "                                       *#*@                      +++++++==-                         ",
    "                                      %%%                                                            ",
    "                                     ##%                                                             ",
    "                                     %%                                                              ",
    "                                    %%%                                                              ",
    "                                   %%%                                                               ",
    "                                    #%                                                 "
};
const int fourmi_height = sizeof(fourmi) / sizeof(fourmi[0]);

const char *fourmiliere[] = {
//     "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::-@@@+::::+-+*#%%%%%%%%%%=+-::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::",
//     "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*%%%%%%#*********************#%%%%%#=:::@@@@:::%%@*#:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::",
    "                                                                                #%%%#++++++++*%%%%%%%%%%%%%%%%%%%%%#*++++++*%%%@:  @#                                                                ",
    "                                                                            %%%+++++*%%%%%*=--------*%%%%%%%%%%%*-----+%%%%%*++++%%@ =                                                           ",
    "                                                                        %%%++++%%%#---------.---%%-               :%%=------:+%%%+++*%%+                                                         ",
    "                                                                    #%*++%%%----------------%+                        %#----------%%%+++%%%                                                    ",
    "                                                                =%%++%%=------------------%:                            =%------------=%%*++#%%                                              ",
    "                                                              %%*+%%*---------------------%::                            %=---------------%%%++#%*                                           ",
    "                                                            %%++%%------------------------%::%:                 :=%%%  #*------------------%%#++%%:                                        ",
    "                                                          %%+*%%-----------=--------------%+::=@#@:::.:::::.=%%=%%++*  +%+----=%%%%%+:------%%*+*%%                                      ",
    "                                                        %%+#%#----------===------------%%  :#%%-:::@@@-:+%%%*=#=*%%---%%  :%%=        %*:-----.%%++%#                                  ",
    "                                                      %%+#%=----------===------------%*  %%-----%%%*%::%+#%%%%----------%%%          ::%:------:%%*+%%                                ",
    "                                                    %%+*%=----------===-----------+%  *%---------------------------------=-         ::::%---------#%*+%@-@*                           ",
    "                                                      +%%-----.----===----  -----%%  %#------------:------:---------------=*@@     ::::::%----------*%*+%% -@@                     ",
    "                                                 %%%%+    %%---+%%+    :=%%%*--%#  #%------.--------------.-----------------%-*@@  ::::::#=-------------.=%++%% - +                ",
    "                                               %%+#%---%%+   :=                %+-----:.--------------.--------------------%  -@@:*:::::#=-------------.=%*+%%                   ",
    "                                             %%+*%+-----:-=%% *:#              +%------.:---%%%%------.------------------------%%=::#:::%%-----------------.=%*+%%             ",
    "                                           %%+#%*--------====%:+@%              %----.----%-    #%%+-------..-----------------  %:##---.-------------------.=%*+%%           ",
    "                                     :@@ %%+#%+-------=======*#:=@#::             %#%%%%%%*    %%%%%  *%---.-------..---------=%%  %--:-----------------------.-%*+%%       ",
    "                                   @@* %%+*%+------=======-====%::%@@:::::     #%+        %%-----:--%%=  :%-------:.-------%%-    =%--------:---------------------#%*+%%    ",
    "                                 :  %%+*%+------===============+%+:@::::::::+%----=#%%%%-----------:--%  -#-----..-------%  +%%%-----------------------------------*%*+%%  ",
    "                                   %%+*%+------====================+%%%%%%%%+===-----------------------#+  %---.:-------.%  %------------------------:----------------*%#+%%:       ",
    "                                 %%+*%=------===================================-----------------------=%  %--.--------  %  %---------------------------.---------------=%%+%%:   = ",
    "                               %#+#%+-----==================================--=------------==-----------%  +%------*%%+      *%%%------===-----=--------..------------------%%+#%#+%@@ ",
    "                        @@@  %%+%%=-----========-==========================-----------*%*    #%=-------%    %%+%:               -%#=--=======-=-----.-----------------------%%++%%:  @@@:-",
    "                      *@@=*%*+%%-------=======%%%%%#====================--=--------%%          %-------=%%                          %*=========-=------------------------------%%*+*%%=+  :",
    "                  +:@%+.%%++%%------=====%%*            -%+==============-=========+%            %-.-------*%                         -%=========-=-------------------------------=%%+++%%  %% ",
    "                  :  *%%++%%-----====#%#:                 %===================:%::           %=*%#%----  :%                            %===========-------------------#%%-:  :#%%-=%  %#%%%%#+++++",
    "                   *%#+#%*--=-====%%:::                   %==================-%::              %%%%*%+-  --+%                            %============--------:------%%            :  %*----:----:+%",
    "                 %%++%%:--=====*%-:::                      %===================-%::             ==%%*%+++++++=%                          %==========-=  ----------#%=           +==  %+--------------",
    "               %%*++%%-========%::::                       %#=+==============#%:::             :%%#%+++++++++#:                        %%#%##%###=-=--=#=:-%%%:              @@@  %---------------",
    "           #%%++%%:=========+%:::::                                    -.@:.::=.:::::           :%%#%++++++++++++%                     ###########@#     :            @@+%*#%%---------------",
};

    const char *carte[] = {
//         "                                                                                                                                                                 ",
//         "                                                                                                                                                                 ",
        "                                              ..... ....................                                                                                       . ",
        "                                      ........===:...-=================.    ........    .......                                                                 ",
        "                               ...-----========-....=================...    ..====:.    ..===..    ..========--:............                              .      ",
        "               ..................=============..=.....-============..         ........    .........========================..................                    ",
        "             ..======= 5 ======-:::::::::......====...:===========-.        ..-= 6 ===:.....===============================================....                  ",
        "             -==========================-.  ....:::...:====:....:-:         :================================================================..       .          ",
        "          ..=======================.....-===... ...:=-..   :----.. .:..================================================================-...                  ",
        "          ..==-....===================....:=======... ... .        . .===...=====================================================.....===-...                    ",
        "          .....    .-===============================.              .=====.:========= 2 ==========================================....  .=..                      ",
        "                   .-================================-.            ..-======= 0 ======================================================-...=..                      ",
        "                 ..:===============================..              ...==== 7 =======================================================-......                      ",
        "                 .==========================::::.                  .....=====================-======================================.  ..                        ",
        "                 .========================.......                  .=======...=-.-============..==================================:....=.                        ",
        "  .              .======================..                         .=====:..  ..=..-============.-==============================-.. .===.                        ",
        "                 .====================:.              .            ......:===.    .....=========================== 8 ===========. .-===..                        ",
        "                 .==================-.                           ...============........=======:==================================. .==..                          ",
        "                 .=================-                           ...-=====================.======-.:==============================. ...                            ",
        "                 ..=========..    -=..                         .-====== 1 ==============..=======-.-============================.                                ",
        "                   ..=======........=:                         .-=======================:..========-......====================:..                                ",
        "                     ..=========..                             .-========================:..=======..    .=======.  -=====-...  .....                            ",
        "                     ....=======..                             .-=========================:..===.....    .=====...  ..======:.  .-=..                            ",
        "                       ......:====..                .          .-==========================:.....        ..-==:.      =-=====.  .-===..                          ",
        "                             ..:==..-========.                 ..-==============================-          .==..      =-..=:..  ...===.                          ",
        "                               ....===========-..                ..=============================-          ...=.      ..=.                                        ",
        "               .                  .========= 9 =:..                ........:===================..                     ....  .-===..                               ",
        "                               ..:================.......                   =================..                       .==...:=====. ..===..                      ",
        "                               ..-=====================:.                   :===============.                           .===.....      -===..                    ",
        "                               ..-========= 3 ==========.                   ..==============.                           ...====:.   .  ..====                    ",
        "                               ..-======================.                     ==============.                             .......        ....                    ",
        "                                  .-==================...                     ==============.                                     .=====:  :=..                  ",
        "                                    .=================.                       ==============.....                               .========--==..                  ",
        "                                      .===============.                       ============...:==.                             .-=============..                  ",
        "                                      .==============..      .                ===========.. .===.                           .:=================..                ",
        "                                      .============..                         .==========.. .===.                           :==================..                ",
        "                                      .============..                       . .-=========.. .==..                           :==================..                ",
        "                                      .===========:..                         ...======.... .....                           :==================..                ",
        "                                .     .=========:..                             .........                                   .::::....-=======..                  ",
        "                                      ..-=====-..                                                                                   ...====:.    ..:====..       ",
        "                                        :====-                                                                                         .=:.    ...====..         ",
        "                                        :====-                                                                                         ..      .====..      .    ",
        "                                        .====-                                                                   .                                                ",
        "                                        .-====...                                                                                                                 ",
        "                                          .====-.         .                                                                                                       ",
        "                                          .......                                                                                                                 ",
    };

void afficherArray(const char *array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%s\n", array[i]);
    }
}

void afficher_fourmi_animation(int position) {
    printf("\033c");
    for (int i = 0; i < HEIGHT; i++) {
            

        if (i < fourmi_height) {
            printf("%*s%s\n", position, "", fourmi[i]);
        } else {
            printf("\n");
        }
    }
}

void afficherMenu_Fourmiliere() {
    printf("\n#=============================== Menu Principal ========================================#");
    printf("\n|                                                                                       |");
    printf("\n|        Quel type de fourmis voulez dans votre fourmilère démarrer la simulation ?     |");
    printf("\n|                          Attention le choix est important                             |");
    printf("\n|                                                                                       |\n");
    printf("| 1. Fourmilière de feuilles                      |    2. Fourmilière de sable          |\n");
    printf("| 3. Fourmilière de pierre                        |    4. Fourmilière tropicale         |\n");
    printf("| 5. Fourmilière forestière                       |    6. Fourmilière désertique        |\n");
    printf("| 7. Fourmilière de champignon                    |    8. Fourmilière aquatique         |\n");
    printf("#=======================================================================================#\n");
}

    // printf("dans quel biome est votre fourmilière ?\n") point_virgule
    // printf("Tapez 0 pour la forêt,\n") point_virgule
    // printf("Tapez 1 pour la desert,\n") point_virgule
    // printf("Tapez 2 pour la plaine,\n") point_virgule
    // printf("Tapez 3 pour la forêt tropicale,\n") point_virgule
    // printf("Tapez 4 pour la ville,\n") point_virgule
    // printf("Tapez 5 pour la toundra,\n") point_virgule
    // printf("Tapez 6 pour la taiga,\n") point_virgule
    // printf("Tapez 7 pour la montagne,\n") point_virgule
    // printf("Tapez 8 pour la haute montagne,\n") point_virgule
    // printf("Tapez 9 pour la mangrove,\n") point_virgule

void afficherMenu_Carte() {
    printf("\n#=============================== Menu Principal ========================================#");
    printf("\n|                                                                                       |");
    printf("\n|            Sur quel emplacement voulez-vous faire démarrer la simulation ?            |");
    printf("\n|                          Attention le choix est important                             |");
    printf("\n|                                                                                       |");
    printf("\n|                             0 : forêt                                                 |");
    printf("\n|                             1 : desert                                                |");
    printf("\n|                             2 : plaine                                                |");
    printf("\n|                             3 : forêt tripicale                                       |");
    //printf("\n|                           4 : ville                                                   |");
    printf("\n|                             5 : toundra                                               |");
    printf("\n|                             6 : taiga                                                 |");
    printf("\n|                             7 : montagne                                              |");
    printf("\n|                             8 : haute montagne                                        |");
    printf("\n|                             9 : mangrove                                              |");
    printf("\n|                                                                                       |\n");
    printf("#=======================================================================================#\n");
}

void afficher_logo(){
    printf("                                                                                      ____  _                 _       _   _               \n");
    printf("                                                                                     / ___|(_)_ __ ___  _   _| | __ _| |_(_) ___  _ __    \n");
    printf("                                                                                     \\___ \\| | '_ ` _ \\| | | | |/ _` | __| |/ _ \\| '_ \\   \n");
    printf("                                                                                      ___) | | | | | | | |_| | | (_| | |_| | (_) | | | |  \n");
    printf("                                                                                     |____/|_|_| |_| |_|\\__,_|_|\\__,_|\\__|_|\\___/|_| |_|  \n");
    printf("                                                                                      / _| ___  _   _ _ __ _ __ ___ (_) (_) ___ _ __ ___  \n");
    printf("                                                                                     | |_ / _ \\| | | | '__| '_ ` _ \\| | | |/ _ \\ '__/ _ \\ \n");
    printf("                                                                                     |  _| (_) | |_| | |  | | | | | | | | |  __/ | |  __/ \n");
    printf("                                                                                     |_|  \\___/ \\__,_|_|  |_| |_| |_|_|_|_|\\___|_|  \\___| \n\n\n");
}

void logo_1(){
    for (int step = 0; step < ANIMATION_STEPS; step++) {
        afficher_fourmi_animation(step);
        usleep(35000);
    }

    afficher_logo();
    getchar();
}

int logo_2(){
    printf("\033[H\033[2J");
    afficherArray(fourmiliere, sizeof(fourmiliere) / sizeof(fourmiliere[0]));
    afficherMenu_Fourmiliere();
    int choix;
    scanf("%d", &choix);
    getchar();
    return choix;
}

int logo_3(){
    printf("\033[H\033[2J");
    afficherArray(carte, sizeof(carte) / sizeof(carte[0]));
    afficherMenu_Carte();
    int choix;
    scanf("%d", &choix);
    getchar();
    return choix;
}

int affichage_animation_debut(){
     logo_1();
    int result = logo_2();
    logo_3();
    return result;
}
