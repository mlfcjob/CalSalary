#ifndef __CAL__SALARY__H
#define __CAL__SALARY__H

#include <gtk/gtk.h>

typedef struct cal_window {
    GtkWidget *window;
    GtkWidget *cal_button;
    GtkWidget *class_subsidy, *class_count;
    GtkWidget *base_pay;
    GtkWidget *social_base;
    GtkWidget *accumulation_fund_base;
    GtkWidget *grid;

    GtkWidget *base_pay_entry;
    GtkWidget *class_subsidy_entry, *class_count_entry;
    GtkWidget *social_base_entry;
    GtkWidget *accumulation_fund_base_entry;

    GtkWidget *show_dialog;

}cal_window;


void init_cal_window(cal_window *win);

float cal_tax(float pre_tax_income);
#endif //__CAL__SALARY__H
