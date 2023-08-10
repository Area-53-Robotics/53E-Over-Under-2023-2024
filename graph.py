import pandas as pd
import matplotlib.pyplot as plt


def plot_csv_columns(csv_file_path, columns_to_plot):
    df = pd.read_csv(csv_file_path)

    columns_data = df[columns_to_plot]

    plt.figure(figsize=(10, 6))

    for col in columns_data.columns:
        plt.plot(columns_data[col], label=col)
    plt.xlabel("Time (50 ms)")
    plt.ylabel("Temperature (C)")
    plt.title("Temperature Over Time")
    plt.legend()

    plt.show()


if __name__ == "__main__":
    csv_file_path = "./log.csv"

    columns_to_plot = ["lt1", "lt2", "lt3"]

    plot_csv_columns(csv_file_path, columns_to_plot)
