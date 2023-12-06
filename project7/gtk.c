#include <gtk/gtk.h>

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *label;

    gtk_init(&argc, &argv);    // GTK 초기화

    // 윈도우 생성 및 설정
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "GTK+ 프로그램");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // 레이블 위젯 생성 및 윈도우에 추가
    label = gtk_label_new("반가워요");
    gtk_container_add(GTK_CONTAINER(window), label);

    // 위젯 표시
    gtk_widget_show_all(window);

    // GTK 메인 루프
    gtk_main();

    return 0;
}
