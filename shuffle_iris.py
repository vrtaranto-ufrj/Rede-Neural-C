import pandas as pd


df = pd.read_csv('iris.data', header=None)
# Shuffle the DataFrame
shuffled_df = df.sample(frac=1, random_state=None).reset_index(drop=True)
# Save the shuffled DataFrame to a new CSV file
shuffled_df.to_csv('shuffled_iris.data', header=False, index=False)

# 80% of the data for training, 20% for testing
train_size = int(0.8 * len(shuffled_df))
train_df = shuffled_df[:train_size]
test_df = shuffled_df[train_size:]

# Normalize the features
train_df.iloc[:, :-1] = (train_df.iloc[:, :-1] - train_df.iloc[:, :-1].min()) / (train_df.iloc[:, :-1].max() - train_df.iloc[:, :-1].min())
test_df.iloc[:, :-1] = (test_df.iloc[:, :-1] - test_df.iloc[:, :-1].min()) / (test_df.iloc[:, :-1].max() - test_df.iloc[:, :-1].min())


# Save the train and test DataFrames to separate CSV files
train_df.to_csv('iris_train.data', header=False, index=False)
test_df.to_csv('iris_test.data', header=False, index=False)