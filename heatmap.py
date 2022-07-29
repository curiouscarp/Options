import seaborn as sns
import pandas as pd
import numpy as np
import matplotlib.pylab as plt

options = pd.read_csv(r'Output/optionsData.csv')
# 30 for the vol (y axis) and 21 for underlying (x axis)
strike_price = ((np.asarray(options['strike_price'])).reshape(30, 21))
option_price = ((np.asarray(options['option_price'])).reshape(30, 21))
delta = ((np.asarray(options['delta'])).reshape(30, 21))
gamma = ((np.asarray(options['gamma'])).reshape(30, 21))
theta = ((np.asarray(options['theta'])).reshape(30, 21))
vega = ((np.asarray(options['vega'])).reshape(30, 21))
rho = ((np.asarray(options['rho'])).reshape(30, 21))

# Create pivot table
result = options.pivot(index='volatility', columns='underlying_price', values='option_price')
result = result.rename_axis("Volatility in annualized standard deviations of log returns")
result = result.rename_axis("Underlying stock price",axis="columns")

# Array for greeks support - to implement
greeks = (np.asarray(["Delta:{0:.3f} \n Gamma:{1:.3f} \n Theta:{2:.3f} "
                      "\n Vega:{3:.3f} \n Rho:{4:.3f}".format(d,g,t,v,r)
                       for d,g,t,v,r in zip(delta.flatten(),
                                            gamma.flatten(),
                                            theta.flatten(),
                                            vega.flatten(),
                                            rho.flatten())])
           ).reshape(30, 21)

# Array for price annotations
prices = [['{:.2f}'.format(item) for item in sublist] for sublist in option_price]

# create plot
fig, ax = plt.subplots(figsize=(30,21))
title = "${} Strike Call Option Prices - 1 year expiry".format((strike_price[0][0]))
plt.title(title,fontsize=16)
ttl = ax.title
ttl.set_position([.5,1.05])

#generate and display heatmap
heatmap = sns.heatmap(result,annot=prices,fmt="",cmap='RdYlGn_r',linewidths=.25,ax=ax)
plt.show()