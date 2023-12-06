#include <gtk/gtk.h>

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // 메인 윈도우 생성
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "간단한 계산기");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);

    // 그리드 레이아웃 생성
    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // 결과창(입력창) 생성
    GtkWidget *entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry, 0, 0, 4, 1);

    // 버튼 생성 및 그리드에 추가
    GtkWidget *button;
    int row, col, num = 1;
    for (row = 1; row < 4; row++) {
        for (col = 0; col < 3; col++) {
            char buf[2];
            snprintf(buf, sizeof(buf), "%d", num);
            button = gtk_button_new_with_label(buf);
            gtk_grid_attach(GTK_GRID(grid), button, col, row, 1, 1);
            num++;
        }
    }

    // 0 및 연산자 버튼 추가
    button = gtk_button_new_with_label("0");
    gtk_grid_attach(GTK_GRID(grid), button, 0, 4, 1, 1);

    button = gtk_button_new_with_label("+");
    gtk_grid_attach(GTK_GRID(grid), button, 1, 4, 1, 1);

    button = gtk_button_new_with_label("-");
    gtk_grid_attach(GTK_GRID(grid), button, 2, 4, 1, 1);

    button = gtk_button_new_with_label("*");
    gtk_grid_attach(GTK_GRID(grid), button, 3, 1, 1, 1);

    button = gtk_button_new_with_label("/");
    gtk_grid_attach(GTK_GRID(grid), button, 3, 2, 1, 1);

    button = gtk_button_new_with_label("=");
    gtk_grid_attach(GTK_GRID(grid), button, 3, 3, 1, 2);

    // 윈도우 종료 시그널
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // 모든 위젯 표시
    gtk_widget_show_all(window);

    gtk_main();
    return 0;
}
