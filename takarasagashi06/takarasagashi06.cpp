#include <stdio.h> // 標準入出力ライブラリのインクルード

// 定数定義
constexpr auto MAX_TRIES = 20;     // 最大試行回数 //constexpr キーワードは、変数の初期化式がコンパイル時に評価されることを保証します。これにより、実行時に値を計算するオーバーヘッドが削減され、パフォーマンスが向上します。
constexpr auto GRID_SIZE = 10;     // 盤面のサイズ //auto キーワードは、変数の型を初期化式の結果から自動的に推論します。constexpr と auto を組み合わせることで、コンパイル時に値が確定する定数値を扱うことができます。

// プロトタイプ宣言
int is_valid_position(int x, int y); // 入力座標の妥当性判定関数のプロトタイプ
int is_treasure_found(int input_x, int input_y, int treasure_x, int treasure_y); // 宝物発見判定関数のプロトタイプ
void show_board_or_error(int input_error, int input_x, int input_y); // 盤面表示またはエラー表示関数のプロトタイプ
void show_result_message(int get_treasure); // 判定結果表示関数のプロトタイプ
int is_game_end(int game_count, int get_treasure); // ゲーム終了判定関数のプロトタイプ
void show_end_message(int get_treasure); // 終了メッセージ表示関数のプロトタイプ

int main() {
    int input_x = 0, input_y = 0; // プレイヤーが入力する列・行
    int treasure_x = 5, treasure_y = 3; // 宝物の位置（列・行）
    int get_treasure = 0;
    int game_count = 0; 

    while (!is_game_end(game_count, get_treasure)) { // ゲーム終了条件を満たすまで繰り返す
        printf("[%d回目] 座標を入力してください。\n", game_count + 1); // 試行回数を表示
        printf("列 = ");
        scanf_s("%d", &input_x);
        printf("行 = ");
        scanf_s("%d", &input_y);

        int input_error = is_valid_position(input_x, input_y); // 入力値の妥当性を判定
        get_treasure = is_treasure_found(input_x, input_y, treasure_x, treasure_y); // 宝物発見判定

        show_board_or_error(input_error, input_x, input_y); // 盤面またはエラー表示

        if (input_error) { // 妥当な入力の場合
            show_result_message(get_treasure); // 判定結果を表示
        }

        if (get_treasure || !input_error) { // 宝物発見またはエラー時
            if (get_treasure) break; // 宝物発見時はループを抜ける
        }

        game_count++;
    }

    show_end_message(get_treasure);

    return 0;
}

// 関数1: 入力座標の妥当性判定
int is_valid_position(int x, int y) {
    if (x < 0 && x >= GRID_SIZE) {
        return 0;
    }
    if (y < 0 && y >= GRID_SIZE) {
        return 0;
    }
    return 1;
}

// 関数2: 入力座標と宝物座標の一致判定
int is_treasure_found(int input_x, int input_y, int treasure_x, int treasure_y) {
   
    if (input_x != treasure_x && input_y != treasure_y) {
        return 0;
    }
    return 1;
}

// 関数3: エラーフラグに応じて盤面表示またはエラーメッセージを表示
// エラー時はエラーメッセージのみ表示
void show_board_or_error(int input_error, int input_x, int input_y) {
    if (input_error) {
        // 盤面を表示
        printf("   ");
        for (int col = 0; col < GRID_SIZE; col++) {
            printf("%2d", col);
        }
        printf("\n");
        for (int row = 0; row < GRID_SIZE; row++) {
            printf("%2d ", row);
            for (int col = 0; col < GRID_SIZE; col++) {
                if (col == input_x && row == input_y) {
                    printf("■ ");
                } else {
                    printf("□ ");
                }
            }
            printf("\n");
        }
    } else {
        printf("エラー：範囲外の入力です。(0から%dの間で入力してください)\n", GRID_SIZE - 1); // エラーメッセージのみ表示
    }
}

// 関数4: 一致判定結果に応じて「はずれ」「あたり」表示
void show_result_message(int get_treasure) {
    if (get_treasure) { // 宝物を発見した場合
        printf("あたり！\n"); // 当たりメッセージ
    } else {
        printf("はずれ。\n"); // 外れメッセージ
    }
}

// 関数5: 20回か一致判定でゲーム終了判定
int is_game_end(int game_count, int get_treasure) {
    if (game_count >= MAX_TRIES) {
        return 1;
	}
    if (get_treasure != 0){
       return 1;
	}
    return 0;
}

// 関数6: 一致判定結果に応じて"COMPLETE" "GAMEOVER"表示
void show_end_message(int get_treasure) {
    if (get_treasure) { // 宝物を発見した場合
        printf("COMPLETE\n"); // 完了メッセージ
    } else {
        printf("GAMEOVER\n"); // ゲームオーバーメッセージ
    }
}

