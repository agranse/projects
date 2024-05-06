import pandas as pd
import matplotlib.pyplot as plt

astar_df = pd.read_csv("astarStratData.csv")

bfs_df = pd.read_csv("bfsStratData.csv")

dfs_df = pd.read_csv("dfsStratData.csv")

dijkstra_df = pd.read_csv("dijkstraStratData.csv")

total_df = pd.read_csv("allData.csv")

deliveries_df = pd.read_csv("onlyDeliveries.csv")

# graph1 = deliveries_df.groupby(["Strategy"]).sum().plot(kind = "bar", y = "Miles", legend = False)
# graph1.set_ylabel("Miles")
# plt.title("Total Miles Traveled Across Simulation Runs")
# plt.show()

#astar: 5 stolen, 5 retrieved, 25 delivered successfully
#bfs: 4 stolen, 4 retrieved, 26 successfully delivered
#dfs: 8 stolen, 5 retrieved, 15 successfully delivered
#dijkstra: 2 stolen, 2 retrieved, 28 successfully delivered

# pie_df = pd.DataFrame({"Status": ["Delivered", "Stolen", "Retrieved"], "Occurences": [94, 16, 19]})
# pie_df.groupby(["Status"]).sum().plot(kind = "pie", y = "Occurences", legend = False)
# plt.title("Status of Package From All Strategies")
# plt.show()

strats = ["AStar", "BFS", "DFS", "Dijkstra"]

# bar_thefts = pd.DataFrame({"Strategy": strats, "Thefts": [5, 4, 8, 2]})
# bar_thefts.groupby(["Strategy"]).sum().plot(kind = "bar", y = "Thefts", legend = False)
# plt.title("Number of Attempted Thefts vs Delivery Strategy")
# plt.show()

# bar_thefts = pd.DataFrame({"Strategy": strats, "Thefts": [0, 0, 3, 0]})
# bar_thefts.groupby(["Strategy"]).sum().plot(kind = "bar", y = "Thefts", legend = False)
# plt.title("Number of Successful Thefts vs Delivery Strategy")
# plt.show()

# bar_dels = pd.DataFrame({"Strategy": strats, "Deliveries": [25, 26, 15, 28]})
# bar_dels.groupby(["Strategy"]).sum().plot(kind = "bar", y = "Deliveries", legend = False)
# plt.title("Number of Successful Deliveries vs Delivery Strategy")
# plt.show()

bar_thefts = pd.read_csv("delsStrat.csv")
print(bar_thefts)
fig, ax = plt.subplots()
bar_thefts.plot(ylabel = "Miles", xlabel = "Delivery Number")
plt.title("Distance in Miles Per Delivery")
plt.show()




