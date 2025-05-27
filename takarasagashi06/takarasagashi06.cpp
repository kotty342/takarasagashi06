#include <stdio.h> // 標準入出力ライブラリのインクルード

// 定数定義
#define TREASURE_COUNT 10    // 宝物の数
#define MAX_TRIES     20     // 最大試行回数
#define GRID_SIZE     10     // 盤面のサイズ

// 盤面を表示する関数
void print_board(int input_col, int input_row) {
    printf("   "); // 列番号の前のスペース
    for (int col = 0; col < GRID_SIZE; col++) { // 列番号を0からGRID_SIZE-1まで表示
        printf("%2d", col);
    }
    printf("\n"); // 改行
    for (int row = 0; row < GRID_SIZE; row++) { // 各行を表示
        printf("%2d ", row); // 行番号を表示
        for (int col = 0; col < GRID_SIZE; col++) { // 各列を表示
            if (col == input_col && row == input_row) { // 入力座標と一致する場合
                printf("■ "); // プレイヤーの入力位置を強調表示
            }
            else {
                printf("□ "); // それ以外は通常のマス
            }
        }
        printf("\n"); // 行の終わりで改行
    }
}

// 関数1: 入力座標の妥当性判定
bool is_valid_input(int x, int y) {
    return (x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE);
}

// 関数2: 宝物との一致判定
bool is_treasure_found(int x, int y, int treasure_x, int treasure_y) {
    return (x == treasure_x && y == treasure_y);
}

// 関数3: 入力値に応じた表示
void show_board_or_error(int x, int y, bool valid) {
    if (valid) {
        print_board(x, y);
    } else {
        printf("エラー：範囲外の入力です。\n");
    }
}

// 関数4: 一致判定結果の表示
void show_hit_or_miss(bool found) {
    if (found) {
        printf("あたり！\n");
    } else {
        printf("はずれ。\n");
    }
}

// 関数5: ゲーム終了判定
bool is_game_end(int tries, bool found) {
    return (tries >= MAX_TRIES || found);
}

// 関数6: ゲーム終了時の表示
void show_game_result(bool found) {
    if (found) {
        printf("COMPLETE\n");
    } else {
        printf("GAMEOVER\n");
    }
}

int main() {
    int input_col, input_row; // プレイヤーが入力する列・行
    int treasure_col = 7, treasure_row = 4; // 宝物の位置（列・行）
    int end_game = 0; // ゲーム終了フラグを初期化

    int i = 0; // 試行回数カウンタ
    while (i < MAX_TRIES) { // 最大試行回数まで繰り返す
        // 入力
        printf("[%d回目] 座標を入力してください。\n", i + 1); // 回数表示
        printf("列 = "); // 列入力を促す
        scanf_s("%d", &input_col); // 列番号の入力
        printf("行 = "); // 行入力を促す
        scanf_s("%d", &input_row); // 行番号の入力

        // 内部演算
        bool valid_input = is_valid_input(input_col, input_row);
        bool found_treasure = is_treasure_found(input_col, input_row, treasure_col, treasure_row);

        // 出力
        show_board_or_error(input_col, input_row, valid_input);

        if (valid_input) {
            show_hit_or_miss(found_treasure);
        }

        if (is_game_end(i + 1, found_treasure)) { // ゲーム終了時
            show_game_result(found_treasure);
            break; // ループを抜ける
        }
        i++; // 試行回数をインクリメント
    }

    return 0; // プログラム終了
}