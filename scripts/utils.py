import pandas as pd
import matplotlib.pyplot as plt

def plot_csv_columns(title, x_label, y_label, csv_file_path, columns_to_plot, column_names):
    df = pd.read_csv(csv_file_path)

    columns_data = df[columns_to_plot]

    plt.figure(figsize=(10, 6))

    for index, col in enumerate(columns_data.columns):
        plt.plot(columns_data[col], label=column_names[index])

    plt.xlabel(x_label)
    plt.ylabel(y_label)
    plt.title(title)

    plt.legend()
    plt.show()
