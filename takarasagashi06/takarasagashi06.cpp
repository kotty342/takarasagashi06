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

int main() {
    int input_col, input_row; // プレイヤーが入力する列・行
    int treasure_col = 7, treasure_row = 4; // 宝物の位置（列・行）
    int input_error, found_treasure, end_game; // 入力エラー判定、宝発見判定、ゲーム終了判定用変数

    end_game = 0; // ゲーム終了フラグを初期化

    int i = 0; // 試行回数カウンタ
    while (i < MAX_TRIES) { // 最大試行回数まで繰り返す
        input_error = 0; // 入力エラーフラグをリセット
        found_treasure = 0; // 宝発見フラグをリセット

        // 入力
        printf("[%d回目] 座標を入力してください。\n", i + 1); // 回数表示
        printf("列 = "); // 列入力を促す
        scanf_s("%d", &input_col); // 列番号の入力
        printf("行 = "); // 行入力を促す
        scanf_s("%d", &input_row); // 行番号の入力

        // 内部演算
        if (input_col < 0 || input_col >= GRID_SIZE || input_row < 0 || input_row >= GRID_SIZE) { // 入力値が範囲外か判定
            input_error = 1; // エラーフラグを立てる
        }
        else if (input_col == treasure_col && input_row == treasure_row) { // 宝の位置と一致するか判定
            found_treasure = 1; // 宝発見フラグを立てる
            end_game = 1; // ゲーム終了フラグを立てる
        }

        // 出力
        if (input_error) { // 入力エラー時
            printf("エラー：範囲外の入力です。\n"); // エラーメッセージ表示
        }
        else {
            print_board(input_col, input_row); // 盤面を表示

            if (found_treasure) { // 宝を発見した場合
                printf("あたり！\n"); // 当たりメッセージ
            }
            else {
                printf("はずれ。\n"); // 外れメッセージ
            }
        }

        if (end_game) { // ゲーム終了時
            printf("COMPLETE\n"); // 完了メッセージ
            break; // ループを抜ける
        }
        i++; // 試行回数をインクリメント
    }

    if (!end_game) { // 最大試行回数以内に宝を発見できなかった場合
        printf("GAMEOVER\n"); // ゲームオーバーメッセージ
    }

    return 0; // プログラム終了
}
