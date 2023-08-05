import pandas as pd
import matplotlib.pyplot as plt


def plot_csv_columns(csv_file_path, columns_to_plot):
    # Read the CSV file into a pandas DataFrame
    df = pd.read_csv(csv_file_path)

    # Extract the desired columns for plotting
    columns_data = df[columns_to_plot]

    # Create the plot
    plt.figure(figsize=(10, 6))  # Optional: Adjust the figure size

    for col in columns_data.columns:
        plt.plot(columns_data[col], label=col)
    # Add labels and legend
    plt.xlabel("Time")
    plt.ylabel("Time (ms)")
    plt.title("Time Over Time")
    plt.legend()

    # Show the plot (optional) or save it to a file
    plt.show()


if __name__ == "__main__":
    # Replace 'your_file.csv' with the actual file path of your CSV file
    csv_file_path = "log.csv"

    # Specify the columns you want to plot (replace with column names from your CSV file)
    columns_to_plot = ["time"]

    # Call the function to plot the specified columns
    plot_csv_columns(csv_file_path, columns_to_plot)
