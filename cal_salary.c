
#include <stdlib.h>
#include "cal_salary.h"

cal_window global_cal_win;

float cal_tax(float pre_tax_income)
{
    float base = pre_tax_income - 3500;
    if (base < 1500) {
        return base * 0.03;
    } else if (base < 4500) {
	return base * 0.1 - 105;
    } else if (base < 9000) {
	return base * 0.2 - 555;
    } else if (base < 35000) {
	return base * 0.25 - 1005;
    } else if (base < 55000) {
	return base * 0.30 - 2755;
    } else if (base < 80000) {
	return base * 0.35 - 5505;
    } else {
	return base * 0.45 - 13505;
    }
}

static void close(GtkWidget *window, gpointer data)
{
    gtk_main_quit();
}

static void cal_salary(GtkWidget *widget, gpointer data)
{
    cal_window *win = (cal_window*)data;

    float salary, tax, final_salary, social_cost, accumulation_cost;
    int i_base, i_class_subsidy, i_class_count, i_social_base, i_accumulation_fund_base;
    const gchar *base, *subsidy, *count, *social, *accumulation;

    GtkWidget *image;
    GtkWidget *hbox;
    GtkWidget *lable;

    base = gtk_entry_get_text(GTK_ENTRY(win->base_pay_entry));
    subsidy = gtk_entry_get_text(GTK_ENTRY(win->class_subsidy_entry));
    count = gtk_entry_get_text(GTK_ENTRY(win->class_count_entry));
    social = gtk_entry_get_text(GTK_ENTRY(win->social_base_entry));
    accumulation = gtk_entry_get_text(GTK_ENTRY(win->accumulation_fund_base_entry));

    i_base = atoi(base);
    i_class_subsidy = atoi(subsidy);
    i_class_count = atoi(count);
    i_social_base = atoi(social);
    i_accumulation_fund_base = atoi(accumulation);

    social_cost = i_social_base * 0.102 + 3;
    accumulation_cost = i_accumulation_fund_base * 0.12;
    salary = i_base + i_class_subsidy * i_class_count - social_cost - accumulation_cost;
    tax = cal_tax(salary);
    final_salary = salary - tax;

    printf("基本工资：%s。, %d.\n", base, i_base);
    printf("课时费：%s。, %d.\n", subsidy, i_class_subsidy);
    printf("课时数：%s。, %d.\n", count, i_class_count);
    printf("社保基数：%s。, %d.\n", social, i_social_base);
    printf("公积金基数：%s。, %d.\n", accumulation, i_accumulation_fund_base);
    printf("扣除个人所得税: %2f.\n", tax);
    printf("社保扣除：%3f, 公积金扣除: %3f, 工资实发为: %3f.\n", social_cost, accumulation_cost, final_salary);

    win->show_dialog = gtk_dialog_new_with_buttons("最终计算结果",
		    GTK_WINDOW(win->window), GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
		    GTK_STOCK_OK, GTK_RESPONSE_OK, NULL);
    image = gtk_image_new_from_stock(GTK_STOCK_DIALOG_INFO, GTK_ICON_SIZE_DIALOG);

    lable = gtk_label_new("社保扣除金额:");
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_container_set_border_width(GTK_CONTAINER(hbox), 10);
    gtk_box_pack_start(GTK_BOX(hbox), image, FALSE, FALSE, FALSE);
    gtk_box_pack_start(GTK_BOX(hbox), lable, FALSE, FALSE, FALSE);
    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(win->show_dialog)), hbox, TRUE, TRUE, FALSE);

    gtk_widget_show_all(win->show_dialog);

    gtk_dialog_run(GTK_DIALOG(win->show_dialog));

}

void init_cal_window(cal_window *win)
{
    win->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(win->window), "薪水计算");
    gtk_window_set_position(GTK_WINDOW(win->window), GTK_WIN_POS_CENTER);
    //gtk_window_set_default_size(GTK_WINDOW(win->window), 800, 600);
    g_signal_connect(win->window, "destroy", G_CALLBACK(close), NULL);


    win->cal_button = gtk_button_new_with_label("计算最终工资");
    g_signal_connect(win->cal_button, "clicked", G_CALLBACK(cal_salary),win);

    win->base_pay = gtk_button_new_with_label("基本工资");
    win->class_subsidy = gtk_button_new_with_label("课时费");
    win->class_count = gtk_button_new_with_label("课时数");
    win->social_base = gtk_button_new_with_label("社保基数");
    win->accumulation_fund_base = gtk_button_new_with_label("公积金基数");

    win->base_pay_entry = gtk_entry_new();
    win->class_subsidy_entry = gtk_entry_new();
    win->class_count_entry = gtk_entry_new();
    win->social_base_entry = gtk_entry_new();
    win->accumulation_fund_base_entry = gtk_entry_new();

    gtk_entry_set_text(GTK_ENTRY(win->base_pay), "请输入基本工资");

    win->grid = gtk_grid_new();
    gtk_grid_attach(GTK_GRID(win->grid), win->base_pay, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(win->grid), win->base_pay_entry, 1, 0, 1, 1);

    gtk_grid_attach(GTK_GRID(win->grid), win->class_subsidy, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(win->grid), win->class_subsidy_entry, 1, 1, 1, 1);

    gtk_grid_attach(GTK_GRID(win->grid), win->class_count, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(win->grid), win->class_count_entry, 1, 2, 1, 1);

    gtk_grid_attach(GTK_GRID(win->grid), win->social_base, 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(win->grid), win->social_base_entry, 1, 3, 1, 1);

    gtk_grid_attach(GTK_GRID(win->grid), win->accumulation_fund_base, 0, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(win->grid), win->accumulation_fund_base_entry, 1, 4, 1, 1);

    gtk_grid_attach(GTK_GRID(win->grid), win->cal_button, 0, 5, 2, 1);
    gtk_container_add(GTK_CONTAINER(win->window), win->grid);


    gtk_widget_show_all(win->window);
}


int main(int argc, char *argv[])
{

    gtk_init(&argc, &argv);

    init_cal_window(&global_cal_win);
    gtk_main();
    return 0;
}
