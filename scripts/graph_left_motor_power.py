from utils import *

if __name__ == "__main__":
    # lp1,lp2,lp3,rp1,rp2,rp3,lt1,lt2,lr3,rt1,rt2,rt3,time
    title = "Left Side Power Over Time"
    x_label = "Time (50 ms)"
    y_label = "Power (W)"
    csv_file_path = "log.csv"
    columns_to_plot = ["lp1", "lp2", "lp3"]
    column_names = ["first motor", "second motor", "third motor"]

    plot_csv_columns(
        title, x_label, y_label, csv_file_path, columns_to_plot, column_names
    )
