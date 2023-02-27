class Piece{
    constructor(piece, pos, color){
        this.piece = piece;
        this.pos = pos;
        this.color = color;
    }
}

let board = [
    [new Piece("R", [0, 0], 0), new Piece("N", [0, 1], 0), new Piece("B", [0, 2], 0), new Piece("Q", [0, 3], 0), new Piece("K", [0, 4], 0), new Piece("B", [0, 5], 0), new Piece("N", [0, 6], 0), new Piece("R", [0, 7], 0)],
    [new Piece("P", [1, 0], 0), new Piece("P", [1, 1], 0), new Piece("P", [1, 2], 0), new Piece("P", [1, 3], 0), new Piece("P", [1, 4], 0), new Piece("P", [1, 5], 0), new Piece("P", [1, 6], 0), new Piece("P", [1, 7], 0)],
    [new Piece(" ", [2, 0], -1), new Piece(" ", [2, 1], -1), new Piece(" ", [2, 2], -1), new Piece(" ", [2, 3], -1), new Piece(" ", [2, 4], -1), new Piece(" ", [2, 5], -1), new Piece(" ", [2, 6], -1), new Piece(" ", [2, 7], -1)],
    [new Piece(" ", [3, 0], -1), new Piece(" ", [3, 1], -1), new Piece(" ", [3, 2], -1), new Piece(" ", [3, 3], -1), new Piece(" ", [3, 4], -1), new Piece(" ", [3, 5], -1), new Piece(" ", [3, 6], -1), new Piece(" ", [3, 7], -1)],
    [new Piece(" ", [4, 0], -1), new Piece(" ", [4, 1], -1), new Piece(" ", [4, 2], -1), new Piece(" ", [4, 3], -1), new Piece(" ", [4, 4], -1), new Piece(" ", [4, 5], -1), new Piece(" ", [4, 6], -1), new Piece(" ", [4, 7], -1)],
    [new Piece(" ", [5, 0], -1), new Piece(" ", [5, 1], -1), new Piece(" ", [5, 2], -1), new Piece(" ", [5, 3], -1), new Piece(" ", [5, 4], -1), new Piece(" ", [5, 5], -1), new Piece(" ", [5, 6], -1), new Piece(" ", [5, 7], -1)],
    [new Piece("P", [6, 0], 1), new Piece("P", [6, 1], 1), new Piece("P", [6, 2], 1), new Piece("P", [6, 3], 1), new Piece("P", [6, 4], 1), new Piece("P", [6, 5], 1), new Piece("P", [6, 6], 1), new Piece("P", [6, 7], 1)],
    [new Piece("R", [7, 0], 1), new Piece("N", [7, 1], 1), new Piece("B", [7, 2], 1), new Piece("Q", [7, 3], 1), new Piece("K", [7, 4], 1), new Piece("B", [7, 5], 1), new Piece("N", [7, 6], 1), new Piece("R", [7, 7], 1)]
]

let boardHTML = document.getElementById("board")

function renderBoard(){
    for(let i = 0; i < 8; i++){
        for(let j = 0; j < 8; j++){
            boardHTML.rows[i].cells[j].setAttribute('id', '')
            boardHTML.rows[i].cells[j].innerHTML = "";
            if(board[i][j].piece !== ' '){
                let img = document.createElement("img");
                let color = board[i][j].color == 0 ? 'b' : 'w';
                boardHTML.rows[i].cells[j].setAttribute('id', `${color}${board[i][j].piece}`)
                img.src = `imgs/${boardHTML.rows[i].cells[j].id}.png`;
                boardHTML.rows[i].cells[j].appendChild(img);
            }
            if((i == 0) && (board[i][j] == 'wP')){
                board[i][j] = 'wQ'
            }else if((i == 7) && (board[i][j] == 'bP')){
                board[i][j] = 'bQ'
            }
        }
    }
}

function addEventListeners(){
    for(let i = 0; i < 8; i++){
        for(let j = 0; j < 8; j++){
            boardHTML.rows[i].cells[j].addEventListener("click", function(event){
                let target1 = event.target
                while(!(target1.classList.contains("square"))){
                    target1 = target1.parentElement
                }
                handleClick(target1)
            })
        }
    }
}


let selectedSquare = null;
        
function handleClick(piece){
    console.log("ASBRHJK")
    let x = piece.parentNode.rowIndex
    let y = piece.cellIndex
    if(whiteTurn && selectedSquare == null){
        if(board[x][y].color == 0){
            return;
        }
    }else if(!whiteTurn && selectedSquare == null){
        if(board[x][y].color == 1){
            return;
        }
    }
    if(board[x][y].piece !== ' ' && selectedSquare == null){
        selectedSquare = [x, y, piece];
        piece.style.backgroundColor = "rgb(130,151,105)"
        // showValidSquares(x, y)
    }else if(selectedSquare && selectedSquare[0] === x && selectedSquare[1] === y){
        selectedSquare = null;
        piece.style.backgroundColor = '';
        // removePotential();
    }else if(selectedSquare){
        movePiece(selectedSquare[0], selectedSquare[1], x, y);
        selectedSquare[2].style.backgroundColor = '';
        selectedSquare = null;
        // removePotential();
    }
}

renderBoard()
addEventListeners()