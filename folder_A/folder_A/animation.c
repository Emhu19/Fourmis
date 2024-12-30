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
        "                                      .============..                         .==========.. .===.                           :========= 4 ======..                ",
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
    printf("\033[H\033[2J");

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
    printf("|                                                                                       |\n");
    printf("#=======================================================================================#\n");
}


void afficherMenu_Carte() {
    printf("\n#=============================== Menu Principal ========================================#");
    printf("\n|                                                                                       |");
    printf("\n|        Quel type de fourmis voulez dans votre fourmilère démarrer la simulation ?     |");
    printf("\n|                          Attention le choix est important                             |");
    printf("\n|                                                                                       |\n");
    printf("| 0. Forêt                                        |    1. Désert                        |\n");
    printf("| 2. Plaine                                       |    3. Forêt tropicale               |\n");
    printf("| 4. Outback australien                           |    5. Toundra                       |\n");
    printf("| 6. Taiga (Forêt boréale)                        |    7. Montagne                      |\n");
    printf("| 8. Haute montagne                               |    9. Mangrove                      |\n");
    printf("|                                                                                       |\n");
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
    printf("\033c");
    afficherArray(fourmiliere, sizeof(fourmiliere) / sizeof(fourmiliere[0]));
    afficherMenu_Fourmiliere();
    int choix;
    do{
        scanf("%d", &choix);
    }while(!((choix>= 1 && choix<9) || choix == 1969));
    getchar();
    return choix;
}

int logo_3(){
    printf("\033c");
    afficherArray(carte, sizeof(carte) / sizeof(carte[0]));
    afficherMenu_Carte();
    int choix;
    do{
        scanf("%d", &choix);
    }while(!((choix>= 0 && choix<10) || choix == 1969));
    
    getchar();
    return choix;
}

int affichage_animation_debut(){
     logo_1();
    int result = logo_2();
    logo_3();
    return result;
}