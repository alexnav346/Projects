let isEmpty = [true, true, true, true, true, true, true, true, true];
var turnOrder = false;
var isGameOver = false;
var playComputer = false;

var decideTurn = firstTurn();
turnOrder = pickTurn(decideTurn);
w = 0;

function computerMove()
{
    var finished = false;
    plzwork = 0;

    while (finished == false)
    {   
        plzwork = Math.floor(Math.random() * 9);
        //alert("plzwork: " + plzwork);

        if (isEmpty[plzwork] == true)
        {
            return plzwork;
            finished = true;
        }
        else
        {
            ;
        }
    }
}

function lockNewGameButton(toLock, newGame)
{
    if (toLock == true)
    {
        newGame.disabled = true;
        newGame.style.display = "none";
    }
    else
    {
        newGame.disabled = false;
        newGame.style.display = "initial";
    }
}

function lockTopButtons(toLock, b1, b2){
    if (toLock == true)
    {
        b1.disabled = true;
        b2.disabled = true;
        //alert("top buttons locked");
    }
    else
    {
        b1.disabled = false;
        b2.disabled = false;
        //alert("top buttons unlocked");
    }
}

function lockBoardButtons(toLock, b0, b1, b2, b3, b4, b5, b6, b7, b8)
{
    if (toLock == true)
    {
        b0.disabled = true;
        b1.disabled = true;
        b2.disabled = true;
        b3.disabled = true;
        b4.disabled = true;
        b5.disabled = true;
        b6.disabled = true;
        b7.disabled = true;
        b8.disabled = true; 
    }
    else
    {
        b0.disabled = false;
        b1.disabled = false;
        b2.disabled = false;
        b3.disabled = false;
        b4.disabled = false;
        b5.disabled = false;
        b6.disabled = false;
        b7.disabled = false;
        b8.disabled = false;
    }
}

function pickTurn(decideTurn)
{
    if (parseInt(decideTurn) == true)
    {
        return false;
    }
    else
    {
        return true;
    }
}

function resetBoard(b0, b1, b2, b3, b4, b5, b6, b7, b8)
{
    b0.innerHTML = "?";
    b1.innerHTML = "?";
    b2.innerHTML = "?";
    b3.innerHTML = "?";
    b4.innerHTML = "?";
    b5.innerHTML = "?";
    b6.innerHTML = "?";
    b7.innerHTML = "?";
    b8.innerHTML = "?";

    isEmpty = [true, true, true, true, true, true, true, true, true];
    
    w = 0;
}

function firstTurn(){
    return Math.floor(Math.random() * Math.floor(2));
}

function changeTurns()
{
    //alert("turnOrder: " + turnOrder);
    
    if (turnOrder == false)
    {
        turnOrder = true;
    }
    else if (turnOrder == true)
    {
        turnOrder = false;
    }
    else
    {
        alert("changeTurns() function not working!!!");
    }

    //alert("new turnOrder: " + turnOrder);
}

function whenButtClicked(buttId, indexNum){
    if (turnOrder == true && isEmpty[indexNum] == true)
    {
        buttId.innerHTML = "X";
        isEmpty[indexNum] = false;
        //alert("isEmpty: " + isEmpty[indexNum]);
        changeTurns(turnOrder);
        w++;
        buttId.disabled = true;
    }
    else if (turnOrder == false && isEmpty[indexNum] == true)
    {
        buttId.innerHTML = "O";
        isEmpty[indexNum] = false;
        //alert("isEmpty: " + isEmpty[indexNum]);
        changeTurns(turnOrder);
        w++
        buttId.disabled = true;
    }
    else if(isEmpty[indexNum] == false)
    {
        //alert("isEmpty == false !!!");
    }
    else
    {
        alert("whenButtClick(), whichTurn != 0||1");
    }
}

function tie()
{
    var msg = document.getElementById("gameOver");    

    if (w == 9)
    {
        //alert("Game Over: Tie!");
        msg.innerHTML = "Game Over: Tie!";
        isGameOver = true;
        
    }
}

function checkWin(x, y, z)
{
    var msg = document.getElementById("gameOver");

    if (x.innerHTML == y.innerHTML && x.innerHTML != "?")
    {
        if (x.innerHTML == z.innerHTML)
        {
            msg.innerHTML = "Game Over: Winner is " + x.innerHTML;
            isGameOver = true;
        }
    }
    else
    {
        //msg.innerHTML = "u fucked up...";
    }
}

function start(){
    //Getting button elemets: Row 1
    let row1 = [document.getElementById("butt00"), 
        document.getElementById("butt01"), document.getElementById("butt02")];

    //Getting button elemets: Row 2
    let row2 = [document.getElementById("butt10"), 
        document.getElementById("butt11"), document.getElementById("butt12")];

    //Getting button elemets: Row 3
    let row3 = [document.getElementById("butt20"), 
    document.getElementById("butt21"), document.getElementById("butt22")];

    var topButton1 = document.getElementById("pvp");
    var topButton2 = document.getElementById("pve");
    var newGameButton = document.getElementById("newGameButton");
    var msg = document.getElementById("gameOver");
    theComputerMove = -1;
    toReturn = 0;

    //locking buttons
    lockBoardButtons(true, row1[0], row1[1], row1[2], row2[0], row2[1], row2[2], row3[0], row3[1], row3[2]);
    //lockTopButtons(true, topButton1, topButton2);

    //unlocking buttons
    lockTopButtons(false, topButton1, topButton2);
    lockNewGameButton(true, newGameButton);
    //lockBoardButtons(false, row1[0], row1[1], row1[2], row2[0], row2[1], row2[2], row3[0], row3[1], row3[2]);

    //standard PvP
    topButton1.addEventListener('click', function(){
        playComputer = false;
        lockTopButtons(true, topButton1, topButton2);
        lockBoardButtons(false, row1[0], row1[1], row1[2], row2[0], row2[1], row2[2], row3[0], row3[1], row3[2]);
    });

    //computer AI
    topButton2.addEventListener('click', function(){
        playComputer = true;
        //alert("playComputer: " + playComputer);
        lockTopButtons(true, topButton1, topButton2);
        lockBoardButtons(false, row1[0], row1[1], row1[2], row2[0], row2[1], row2[2], row3[0], row3[1], row3[2]);
    });

    //setting up "click" listeners
    //changes innerHTML
    {
        row1[0].addEventListener('click', function(){
            whenButtClicked(row1[0], 0);
            tie();
            checkWin(...row1);
            checkWin(...row2);
            checkWin(...row3);
            checkWin(row1[0], row2[0], row3[0]);
            checkWin(row1[1], row2[1], row3[1]);
            checkWin(row1[2], row2[2], row3[2]);
            checkWin(row1[0], row2[1], row3[2]);
            checkWin(row1[2], row2[1], row3[0]);

            //if playing against the computer
            if(playComputer == true && w < 8)
            {
                //this should return the index number of button (0-8)
                //Row1: 0, 1, 2    Row2: 3, 4, 5  Row3: 6, 7, 8
                theComputerMove = computerMove();

                //alert("theComputerMove: " + theComputerMove);

                if (theComputerMove == 0 || theComputerMove == 1 || theComputerMove == 2)
                {
                    whenButtClicked(row1[theComputerMove], theComputerMove);
                }
                else if (theComputerMove == 3 || theComputerMove == 4 || theComputerMove == 5)
                {
                    if (theComputerMove == 3)
                    {
                        toReturn = 0;
                    }
                    else if (theComputerMove == 4)
                    {
                        toReturn = 1;
                    }
                    else if (theComputerMove == 5)
                    {
                        toReturn = 2;
                    }

                    whenButtClicked(row2[toReturn], theComputerMove);
                }
                else if (theComputerMove == 6 || theComputerMove == 7 || theComputerMove == 8)
                {
                    if (theComputerMove == 6)
                    {
                        toReturn = 0;
                    }
                    else if (theComputerMove == 7)
                    {
                        toReturn = 1;
                    }
                    else if (theComputerMove == 8)
                    {
                        toReturn = 2;
                    }

                    whenButtClicked(row3[toReturn], theComputerMove);
                }
                tie();
                checkWin(...row1);
                checkWin(...row2);
                checkWin(...row3);
                checkWin(row1[0], row2[0], row3[0]);
                checkWin(row1[1], row2[1], row3[1]);
                checkWin(row1[2], row2[2], row3[2]);
                checkWin(row1[0], row2[1], row3[2]);
                checkWin(row1[2], row2[1], row3[0]);
            }

            if (isGameOver == true)
            {
                lockBoardButtons(true, row1[0], row1[1], row1[2], row2[0], row2[1], row2[2], row3[0], row3[1], row3[2]);
                lockNewGameButton(false, newGameButton);
                newGameButton.addEventListener('click', function(){
                    resetBoard(row1[0], row1[1], row1[2], row2[0], row2[1], row2[2], row3[0], row3[1], row3[2]);
                    lockBoardButtons(true, row1[0], row1[1], row1[2], row2[0], row2[1], row2[2], row3[0], row3[1], row3[2]);
                    lockTopButtons(false, topButton1, topButton2);
                    lockNewGameButton(true, newGameButton);
                    isGameOver = false;
                    msg.innerHTML = "";
                    playComptuer = false;
                    decideTurn = firstTurn();
                    turnOrder = pickTurn(decideTurn);
                });
            }
        });
        
        row1[1].addEventListener('click', function(){
            whenButtClicked(row1[1], 1);
            tie();
            checkWin(...row1);
            checkWin(...row2);
            checkWin(...row3);
            checkWin(row1[0], row2[0], row3[0]);
            checkWin(row1[1], row2[1], row3[1]);
            checkWin(row1[2], row2[2], row3[2]);
            checkWin(row1[0], row2[1], row3[2]);
            checkWin(row1[2], row2[1], row3[0]);

            //if playing against the computer
            if(playComputer == true && w < 8)
            {
                //this should return the index number of button (0-8)
                //Row1: 0, 1, 2    Row2: 3, 4, 5  Row3: 6, 7, 8
                theComputerMove = computerMove();

                //alert("theComputerMove: " + theComputerMove);

                if (theComputerMove == 0 || theComputerMove == 1 || theComputerMove == 2)
                {
                    whenButtClicked(row1[theComputerMove], theComputerMove);
                }
                else if (theComputerMove == 3 || theComputerMove == 4 || theComputerMove == 5)
                {
                    if (theComputerMove == 3)
                    {
                        toReturn = 0;
                    }
                    else if (theComputerMove == 4)
                    {
                        toReturn = 1;
                    }
                    else if (theComputerMove == 5)
                    {
                        toReturn = 2;
                    }
                    whenButtClicked(row2[toReturn], theComputerMove);
                }
                else if (theComputerMove == 6 || theComputerMove == 7 || theComputerMove == 8)
                {
                    if (theComputerMove == 6)
                    {
                        toReturn = 0;
                    }
                    else if (theComputerMove == 7)
                    {
                        toReturn = 1;
                    }
                    else if (theComputerMove == 8)
                    {
                        toReturn = 2;
                    }
                    whenButtClicked(row3[toReturn], theComputerMove);
                }
                else
                {
                    alert("out of bounds theComputerMove: " + theComputerMove);
                }
                tie();
                checkWin(...row1);
                checkWin(...row2);
                checkWin(...row3);
                checkWin(row1[0], row2[0], row3[0]);
                checkWin(row1[1], row2[1], row3[1]);
                checkWin(row1[2], row2[2], row3[2]);
                checkWin(row1[0], row2[1], row3[2]);
                checkWin(row1[2], row2[1], row3[0]);
            }

            if (isGameOver == true)
            {
                lockBoardButtons(true, row1[0], row1[1], row1[2], row2[0], row2[1], row2[2], row3[0], row3[1], row3[2]);
                lockNewGameButton(false, newGameButton);
                newGameButton.addEventListener('click', function(){
                    resetBoard(row1[0], row1[1], row1[2], row2[0], row2[1], row2[2], row3[0], row3[1], row3[2]);
                    lockBoardButtons(true, row1[0], row1[1], row1[2], row2[0], row2[1], row2[2], row3[0], row3[1], row3[2]);
                    lockTopButtons(false, topButton1, topButton2);
                    lockNewGameButton(true, newGameButton);
                    isGameOver = false;
                    msg.innerHTML = "";
                    playComptuer = false;
                    decideTurn = firstTurn();
                    turnOrder = pickTurn(decideTurn);
                });
            }
        });
        
        row1[2].addEventListener('click', function(){
            whenButtClicked(row1[2], 2);
            tie();
            checkWin(...row1);
            checkWin(...row2);
            checkWin(...row3);
            checkWin(row1[0], row2[0], row3[0]);
            checkWin(row1[1], row2[1], row3[1]);
            checkWin(row1[2], row2[2], row3[2]);
            checkWin(row1[0], row2[1], row3[2]);
            checkWin(row1[2], row2[1], row3[0]);

            //if playing against the computer
            if(playComputer == true && w < 8)
            {
                //this should return the index number of button (0-8)
                //Row1: 0, 1, 2    Row2: 3, 4, 5  Row3: 6, 7, 8
                theComputerMove = computerMove();

                //alert("theComputerMove: " + theComputerMove);

                if (theComputerMove == 0 || theComputerMove == 1 || theComputerMove == 2)
                {
                    whenButtClicked(row1[theComputerMove], theComputerMove);
                }
                else if (theComputerMove == 3 || theComputerMove == 4 || theComputerMove == 5)
                {
                    if (theComputerMove == 3)
                    {
                        toReturn = 0;
                    }
                    else if (theComputerMove == 4)
                    {
                        toReturn = 1;
                    }
                    else if (theComputerMove == 5)
                    {
                        toReturn = 2;
                    }
                    whenButtClicked(row2[toReturn], theComputerMove);
                }
                else if (theComputerMove == 6 || theComputerMove == 7 || theComputerMove == 8)
                {
                    if (theComputerMove == 6)
                    {
                        toReturn = 0;
                    }
                    else if (theComputerMove == 7)
                    {
                        toReturn = 1;
                    }
                    else if (theComputerMove == 8)
                    {
                        toReturn = 2;
                    }
                    whenButtClicked(row3[toReturn], theComputerMove);
                }
                tie();
                checkWin(...row1);
                checkWin(...row2);
                checkWin(...row3);
                checkWin(row1[0], row2[0], row3[0]);
                checkWin(row1[1], row2[1], row3[1]);
                checkWin(row1[2], row2[2], row3[2]);
                checkWin(row1[0], row2[1], row3[2]);
                checkWin(row1[2], row2[1], row3[0]);
            }

            if (isGameOver == true)
            {
                lockBoardButtons(true, row1[0], row1[1], row1[2], row2[0], row2[1], row2[2], row3[0], row3[1], row3[2]);
                lockNewGameButton(false, newGameButton);
                newGameButton.addEventListener('click', function(){
                    resetBoard(row1[0], row1[1], row1[2], row2[0], row2[1], row2[2], row3[0], row3[1], row3[2]);
                    lockBoardButtons(true, row1[0], row1[1], row1[2], row2[0], row2[1], row2[2], row3[0], row3[1], row3[2]);
                    lockTopButtons(false, topButton1, topButton2);
                    lockNewGameButton(true, newGameButton);
                    isGameOver = false;
                    msg.innerHTML = "";
                    playComptuer = false;
                    decideTurn = firstTurn();
                    turnOrder = pickTurn(decideTurn);
                });
            }
        });
        
        row2[0].addEventListener('click', function(){
            whenButtClicked(row2[0], 3);
            tie();
            checkWin(...row1);
            checkWin(...row2);
            checkWin(...row3);
            checkWin(row1[0], row2[0], row3[0]);
            checkWin(row1[1], row2[1], row3[1]);
            checkWin(row1[2], row2[2], row3[2]);
            checkWin(row1[0], row2[1], row3[2]);
            checkWin(row1[2], row2[1], row3[0]);

            //if playing against the computer
            if(playComputer == true && w < 8)
            {
                //this should return the index number of button (0-8)
                //Row1: 0, 1, 2    Row2: 3, 4, 5  Row3: 6, 7, 8
                theComputerMove = computerMove();

                //alert("theComputerMove: " + theComputerMove);

                if (theComputerMove == 0 || theComputerMove == 1 || theComputerMove == 2)
                {
                    whenButtClicked(row1[theComputerMove], theComputerMove);
                }
                else if (theComputerMove == 3 || theComputerMove == 4 || theComputerMove == 5)
                {
                    if (theComputerMove == 3)
                    {
                        toReturn = 0;
                    }
                    else if (theComputerMove == 4)
                    {
                        toReturn = 1;
                    }
                    else if (theComputerMove == 5)
                    {
                        toReturn = 2;
                    }

                    whenButtClicked(row2[toReturn], theComputerMove);
                }
                else if (theComputerMove == 6 || theComputerMove == 7 || theComputerMove == 8)
                {
                    if (theComputerMove == 6)
                    {
                        toReturn = 0;
                    }
                    else if (theComputerMove == 7)
                    {
                        toReturn = 1;
                    }
                    else if (theComputerMove == 8)
                    {
                        toReturn = 2;
                    }

                    whenButtClicked(row3[toReturn], theComputerMove);
                }
                tie();
                checkWin(...row1);
                checkWin(...row2);
                checkWin(...row3);
                checkWin(row1[0], row2[0], row3[0]);
                checkWin(row1[1], row2[1], row3[1]);
                checkWin(row1[2], row2[2], row3[2]);
                checkWin(row1[0], row2[1], row3[2]);
                checkWin(row1[2], row2[1], row3[0]);
            }

            if (isGameOver == true)
            {
                lockBoardButtons(true, row1[0], row1[1], row1[2], row2[0], row2[1], row2[2], row3[0], row3[1], row3[2]);
                lockNewGameButton(false, newGameButton);
                newGameButton.addEventListener('click', function(){
                    resetBoard(row1[0], row1[1], row1[2], row2[0], row2[1], row2[2], row3[0], row3[1], row3[2]);
                    lockBoardButtons(true, row1[0], row1[1], row1[2], row2[0], row2[1], row2[2], row3[0], row3[1], row3[2]);
                    lockTopButtons(false, topButton1, topButton2);
                    lockNewGameButton(true, newGameButton);
                    isGameOver = false;
                    msg.innerHTML = "";
                    playComptuer = false;
                    decideTurn = firstTurn();
                    turnOrder = pickTurn(decideTurn);
                });
            }
        });
        
        row2[1].addEventListener('click', function(){
            whenButtClicked(row2[1], 4);
            tie();
            checkWin(...row1);
            checkWin(...row2);
            checkWin(...row3);
            checkWin(row1[0], row2[0], row3[0]);
            checkWin(row1[1], row2[1], row3[1]);
            checkWin(row1[2], row2[2], row3[2]);
            checkWin(row1[0], row2[1], row3[2]);
            checkWin(row1[2], row2[1], row3[0]);

            //if playing against the computer
            if(playComputer == true && w < 8)
            {
                //this should return the index number of button (0-8)
                //Row1: 0, 1, 2    Row2: 3, 4, 5  Row3: 6, 7, 8
                theComputerMove = computerMove();

                //alert("theComputerMove: " + theComputerMove);

                if (theComputerMove == 0 || theComputerMove == 1 || theComputerMove == 2)
                {
                    whenButtClicked(row1[theComputerMove], theComputerMove);
                }
                else if (theComputerMove == 3 || theComputerMove == 4 || theComputerMove == 5)
                {
                    if (theComputerMove == 3)
                    {
                        toReturn = 0;
                    }
                    else if (theComputerMove == 4)
                    {
                        toReturn = 1;
                    }
                    else if (theComputerMove == 5)
                    {
                        toReturn = 2;
                    }

                    whenButtClicked(row2[toReturn], theComputerMove);
                }
                else if (theComputerMove == 6 || theComputerMove == 7 || theComputerMove == 8)
                {
                    if (theComputerMove == 6)
                    {
                        toReturn = 0;
                    }
                    else if (theComputerMove == 7)
                    {
                        toReturn = 1;
                    }
                    else if (theComputerMove == 8)
                    {
                        toReturn = 2;
                    }

                    whenButtClicked(row3[toReturn], theComputerMove);
                }
                tie();
                checkWin(...row1);
                checkWin(...row2);
                checkWin(...row3);
                checkWin(row1[0], row2[0], row3[0]);
                checkWin(row1[1], row2[1], row3[1]);
                checkWin(row1[2], row2[2], row3[2]);
                checkWin(row1[0], row2[1], row3[2]);
                checkWin(row1[2], row2[1], row3[0]);
            }

            if (isGameOver == true)
            {
                lockBoardButtons(true, row1[0], row1[1], row1[2], row2[0], row2[1], row2[2], row3[0], row3[1], row3[2]);
                lockNewGameButton(false, newGameButton);
                newGameButton.addEventListener('click', function(){
                    resetBoard(row1[0], row1[1], row1[2], row2[0], row2[1], row2[2], row3[0], row3[1], row3[2]);
                    lockBoardButtons(true, row1[0], row1[1], row1[2], row2[0], row2[1], row2[2], row3[0], row3[1], row3[2]);
                    lockTopButtons(false, topButton1, topButton2);
                    lockNewGameButton(true, newGameButton);
                    isGameOver = false;
                    msg.innerHTML = "";
                    playComptuer = false;
                    decideTurn = firstTurn();
                    turnOrder = pickTurn(decideTurn);
                });
            }
        });
        
        row2[2].addEventListener('click', function(){
            whenButtClicked(row2[2], 5);
            tie();
            checkWin(...row1);
            checkWin(...row2);
            checkWin(...row3);
            checkWin(row1[0], row2[0], row3[0]);
            checkWin(row1[1], row2[1], row3[1]);
            checkWin(row1[2], row2[2], row3[2]);
            checkWin(row1[0], row2[1], row3[2]);
            checkWin(row1[2], row2[1], row3[0]);

            //if playing against the computer
            if(playComputer == true && w < 8)
            {
                //this should return the index number of button (0-8)
                //Row1: 0, 1, 2    Row2: 3, 4, 5  Row3: 6, 7, 8
                theComputerMove = computerMove();

                //alert("theComputerMove: " + theComputerMove);

                if (theComputerMove == 0 || theComputerMove == 1 || theComputerMove == 2)
                {
                    whenButtClicked(row1[theComputerMove], theComputerMove);
                }
                else if (theComputerMove == 3 || theComputerMove == 4 || theComputerMove == 5)
                {
                    if (theComputerMove == 3)
                    {
                        toReturn = 0;
                    }
                    else if (theComputerMove == 4)
                    {
                        toReturn = 1;
                    }
                    else if (theComputerMove == 5)
                    {
                        toReturn = 2;
                    }

                    whenButtClicked(row2[toReturn], theComputerMove);
                }
                else if (theComputerMove == 6 || theComputerMove == 7 || theComputerMove == 8)
                {
                    if (theComputerMove == 6)
                    {
                        toReturn = 0;
                    }
                    else if (theComputerMove == 7)
                    {
                        toReturn = 1;
                    }
                    else if (theComputerMove == 8)
                    {
                        toReturn = 2;
                    }

                    whenButtClicked(row3[toReturn], theComputerMove);
                }
                tie();
                checkWin(...row1);
                checkWin(...row2);
                checkWin(...row3);
                checkWin(row1[0], row2[0], row3[0]);
                checkWin(row1[1], row2[1], row3[1]);
                checkWin(row1[2], row2[2], row3[2]);
                checkWin(row1[0], row2[1], row3[2]);
                checkWin(row1[2], row2[1], row3[0]);
            }

            if (isGameOver == true)
            {
                lockBoardButtons(true, row1[0], row1[1], row1[2], row2[0], row2[1], row2[2], row3[0], row3[1], row3[2]);
                lockNewGameButton(false, newGameButton);
                newGameButton.addEventListener('click', function(){
                    resetBoard(row1[0], row1[1], row1[2], row2[0], row2[1], row2[2], row3[0], row3[1], row3[2]);
                    lockBoardButtons(true, row1[0], row1[1], row1[2], row2[0], row2[1], row2[2], row3[0], row3[1], row3[2]);
                    lockTopButtons(false, topButton1, topButton2);
                    lockNewGameButton(true, newGameButton);
                    isGameOver = false;
                    msg.innerHTML = "";
                    playComptuer = false;
                    decideTurn = firstTurn();
                    turnOrder = pickTurn(decideTurn);
                });
            }
        });
        
        row3[0].addEventListener('click', function(){
            whenButtClicked(row3[0], 6);
            tie();
            checkWin(...row1);
            checkWin(...row2);
            checkWin(...row3);
            checkWin(row1[0], row2[0], row3[0]);
            checkWin(row1[1], row2[1], row3[1]);
            checkWin(row1[2], row2[2], row3[2]);
            checkWin(row1[0], row2[1], row3[2]);
            checkWin(row1[2], row2[1], row3[0]);

            //if playing against the computer
            if(playComputer == true && w < 8)
            {
                //this should return the index number of button (0-8)
                //Row1: 0, 1, 2    Row2: 3, 4, 5  Row3: 6, 7, 8
                theComputerMove = computerMove();

                //alert("theComputerMove: " + theComputerMove);

                if (theComputerMove == 0 || theComputerMove == 1 || theComputerMove == 2)
                {
                    whenButtClicked(row1[theComputerMove], theComputerMove);
                }
                else if (theComputerMove == 3 || theComputerMove == 4 || theComputerMove == 5)
                {
                    if (theComputerMove == 3)
                    {
                        toReturn = 0;
                    }
                    else if (theComputerMove == 4)
                    {
                        toReturn = 1;
                    }
                    else if (theComputerMove == 5)
                    {
                        toReturn = 2;
                    }

                    whenButtClicked(row2[toReturn], theComputerMove);
                }
                else if (theComputerMove == 6 || theComputerMove == 7 || theComputerMove == 8)
                {
                    if (theComputerMove == 6)
                    {
                        toReturn = 0;
                    }
                    else if (theComputerMove == 7)
                    {
                        toReturn = 1;
                    }
                    else if (theComputerMove == 8)
                    {
                        toReturn = 2;
                    }

                    whenButtClicked(row3[toReturn], theComputerMove);
                }
                tie();
                checkWin(...row1);
                checkWin(...row2);
                checkWin(...row3);
                checkWin(row1[0], row2[0], row3[0]);
                checkWin(row1[1], row2[1], row3[1]);
                checkWin(row1[2], row2[2], row3[2]);
                checkWin(row1[0], row2[1], row3[2]);
                checkWin(row1[2], row2[1], row3[0]);
            }

            if (isGameOver == true)
            {
                lockBoardButtons(true, row1[0], row1[1], row1[2], row2[0], row2[1], row2[2], row3[0], row3[1], row3[2]);
                lockNewGameButton(false, newGameButton);
                newGameButton.addEventListener('click', function(){
                    resetBoard(row1[0], row1[1], row1[2], row2[0], row2[1], row2[2], row3[0], row3[1], row3[2]);
                    lockBoardButtons(true, row1[0], row1[1], row1[2], row2[0], row2[1], row2[2], row3[0], row3[1], row3[2]);
                    lockTopButtons(false, topButton1, topButton2);
                    lockNewGameButton(true, newGameButton);
                    isGameOver = false;
                    msg.innerHTML = "";
                    playComptuer = false;
                    decideTurn = firstTurn();
                    turnOrder = pickTurn(decideTurn);
                });
            }
        });
        
        row3[1].addEventListener('click', function(){
            whenButtClicked(row3[1], 7);
            tie();
            checkWin(...row1);
            checkWin(...row2);
            checkWin(...row3);
            checkWin(row1[0], row2[0], row3[0]);
            checkWin(row1[1], row2[1], row3[1]);
            checkWin(row1[2], row2[2], row3[2]);
            checkWin(row1[0], row2[1], row3[2]);
            checkWin(row1[2], row2[1], row3[0]);

            //if playing against the computer
            if(playComputer == true && w < 8)
            {
                //this should return the index number of button (0-8)
                //Row1: 0, 1, 2    Row2: 3, 4, 5  Row3: 6, 7, 8
                theComputerMove = computerMove();

                //alert("theComputerMove: " + theComputerMove);

                if (theComputerMove == 0 || theComputerMove == 1 || theComputerMove == 2)
                {
                    whenButtClicked(row1[theComputerMove], theComputerMove);
                }
                else if (theComputerMove == 3 || theComputerMove == 4 || theComputerMove == 5)
                {
                    if (theComputerMove == 3)
                    {
                        toReturn = 0;
                    }
                    else if (theComputerMove == 4)
                    {
                        toReturn = 1;
                    }
                    else if (theComputerMove == 5)
                    {
                        toReturn = 2;
                    }

                    whenButtClicked(row2[toReturn], theComputerMove);
                }
                else if (theComputerMove == 6 || theComputerMove == 7 || theComputerMove == 8)
                {
                    if (theComputerMove == 6)
                    {
                        toReturn = 0;
                    }
                    else if (theComputerMove == 7)
                    {
                        toReturn = 1;
                    }
                    else if (theComputerMove == 8)
                    {
                        toReturn = 2;
                    }

                    whenButtClicked(row3[toReturn], theComputerMove);
                }
                tie();
                checkWin(...row1);
                checkWin(...row2);
                checkWin(...row3);
                checkWin(row1[0], row2[0], row3[0]);
                checkWin(row1[1], row2[1], row3[1]);
                checkWin(row1[2], row2[2], row3[2]);
                checkWin(row1[0], row2[1], row3[2]);
                checkWin(row1[2], row2[1], row3[0]);
            }

            if (isGameOver == true)
            {
                lockBoardButtons(true, row1[0], row1[1], row1[2], row2[0], row2[1], row2[2], row3[0], row3[1], row3[2]);
                lockNewGameButton(false, newGameButton);
                newGameButton.addEventListener('click', function(){
                    resetBoard(row1[0], row1[1], row1[2], row2[0], row2[1], row2[2], row3[0], row3[1], row3[2]);
                    lockBoardButtons(true, row1[0], row1[1], row1[2], row2[0], row2[1], row2[2], row3[0], row3[1], row3[2]);
                    lockTopButtons(false, topButton1, topButton2);
                    lockNewGameButton(true, newGameButton);
                    isGameOver = false;
                    msg.innerHTML = "";
                    playComptuer = false;
                    decideTurn = firstTurn();
                    turnOrder = pickTurn(decideTurn);
                });
            }
        });
        
        row3[2].addEventListener('click', function(){
            whenButtClicked(row3[2], 8);
            tie();
            checkWin(...row1);
            checkWin(...row2);
            checkWin(...row3);
            checkWin(row1[0], row2[0], row3[0]);
            checkWin(row1[1], row2[1], row3[1]);
            checkWin(row1[2], row2[2], row3[2]);
            checkWin(row1[0], row2[1], row3[2]);
            checkWin(row1[2], row2[1], row3[0]);

            //if playing against the computer
            if(playComputer == true && w < 8)
            {
                //this should return the index number of button (0-8)
                //Row1: 0, 1, 2    Row2: 3, 4, 5  Row3: 6, 7, 8
                theComputerMove = computerMove();

                //alert("theComputerMove: " + theComputerMove);

                if (theComputerMove == 0 || theComputerMove == 1 || theComputerMove == 2)
                {
                    whenButtClicked(row1[theComputerMove], theComputerMove);
                }
                else if (theComputerMove == 3 || theComputerMove == 4 || theComputerMove == 5)
                {
                    if (theComputerMove == 3)
                    {
                        toReturn = 0;
                    }
                    else if (theComputerMove == 4)
                    {
                        toReturn = 1;
                    }
                    else if (theComputerMove == 5)
                    {
                        toReturn = 2;
                    }

                    whenButtClicked(row2[toReturn], theComputerMove);
                }
                else if (theComputerMove == 6 || theComputerMove == 7 || theComputerMove == 8)
                {
                    if (theComputerMove == 6)
                    {
                        toReturn = 0;
                    }
                    else if (theComputerMove == 7)
                    {
                        toReturn = 1;
                    }
                    else if (theComputerMove == 8)
                    {
                        toReturn = 2;
                    }

                    whenButtClicked(row3[toReturn], theComputerMove);
                }
                tie();
                checkWin(...row1);
                checkWin(...row2);
                checkWin(...row3);
                checkWin(row1[0], row2[0], row3[0]);
                checkWin(row1[1], row2[1], row3[1]);
                checkWin(row1[2], row2[2], row3[2]);
                checkWin(row1[0], row2[1], row3[2]);
                checkWin(row1[2], row2[1], row3[0]);
            }

            if (isGameOver == true)
            {
                lockBoardButtons(true, row1[0], row1[1], row1[2], row2[0], row2[1], row2[2], row3[0], row3[1], row3[2]);
                lockNewGameButton(false, newGameButton);
                newGameButton.addEventListener('click', function(){
                    resetBoard(row1[0], row1[1], row1[2], row2[0], row2[1], row2[2], row3[0], row3[1], row3[2]);
                    lockBoardButtons(true, row1[0], row1[1], row1[2], row2[0], row2[1], row2[2], row3[0], row3[1], row3[2]);
                    lockTopButtons(false, topButton1, topButton2);
                    lockNewGameButton(true, newGameButton);
                    isGameOver = false;
                    msg.innerHTML = "";
                    playComptuer = false;
                    decideTurn = firstTurn();
                    turnOrder = pickTurn(decideTurn);
                });
            }
        });
    }   
}

window.addEventListener('load', function(){
    start();
});