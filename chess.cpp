#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "ChessBoardClass.h"

using namespace std;

int main(){
    ChessBoard game;
    cout<<endl<<"* Chesscomputer v.0.1"<<endl;
    game.printHelp();
    bool gameon=true;
    init();
    while(gameon){
        game.reset();
        string pick_side = "";
        while(pick_side != "b" && pick_side != "w" && pick_side != "q"){
            cout<<endl<<"Play as (b)lack or (w)hite or (q)uit? ";
            cin>>pick_side;
        }
        string diff;
        while(diff != "e" && diff != "m" && diff != "h") {
            cout << endl << "Choose difficulty level : (e)asy, (m)edium, (h)ard" << endl;
            cin >> diff;
        }
        game.setdifficulty(diff);
        if(pick_side == "q"){
            cout<<"Good bye."<<endl;
            break;
        }

        if(pick_side == "b")
            game.AIMove();
        else
            game.printBoard();

        while(gameon = game.promptInput()){
            if(!game.hasKing()){
                cout<<"* You are victorious!"<<endl;
                break;
            }
            game.AIMove();
            if(!game.hasKing()){
                cout<<"* You are defeated!"<<endl;
                break;
            }
        }
    }
    return 0;
}
