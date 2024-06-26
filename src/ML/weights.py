import numpy as np
import sys
import pandas as pd
from sklearn.linear_model import LinearRegression


if __name__ == "__main__":
    # Load data from CSV
    data = pd.read_csv('data.csv')
    X = data[['ADC']].values  #ADC is the name of the first column
    Y = data['mA'].values  #mA is the name of the second column

    # Perform linear regression
    model = LinearRegression()
    model.fit(X, Y)

    slope = model.coef_[0]
    intercept = model.intercept_

    print("I pesi ottenuti massaggiando i dati sono: ")
    print(f"Slope: {slope}")
    print(f"Intercept: {intercept}")

    # Predict Y values
    Y_pred = model.predict(X)

    #for every Y value in Y_pred, if it is less than 0, set it to 0
    Y_pred = [0 if y < 0 else y for y in Y_pred]

    print("Bovinamente l'errore è:")

    #print MSE, Root MSE and MAE
    mse = np.mean((Y - Y_pred) ** 2) 
    rmse = np.sqrt(mse)
    mae = np.mean(np.abs(Y - Y_pred))

    print(f"MSE: {mse}")
    print(f"Root MSE: {rmse}")
    print(f"MAE: {mae}")
    sys.exit(0)