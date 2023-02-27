all:
	gcc CFiles/main.c CFiles/move_logic.c -o sushibot

wasm:
	emcc WasmFiles/main.c WasmFiles/move_logic.c -o GameFiles/chess.js -s NO_EXIT_RUNTIME=1 -s EXPORTED_RUNTIME_METHODS=[ccall]
