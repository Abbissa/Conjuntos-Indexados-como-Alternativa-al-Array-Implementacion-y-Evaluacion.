import os
from pathlib import Path

import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
gen = {"GenRandom": "Valores aleatorios", "GenOrdered": "Valores ordenados",
    "GenInverse": "Valores inversamente ordenados"}
tests = {"INSERT": "Inserción", "USAGE": "Uso", "REMOVE": "Borrado"}
object ={"Small": "Pequeño", "Medium": "Mediano", "Large": "Grande"}
colores = {"TestBinaryHeap": '#1b9e77', "TestSet": "black", 
    "ptrHollowList-128": '#f768a1',"ptrHollowList-256": '#ae017e', 
    "ptrHollowList-512": '#49006a', "HollowList-128": '#fc8d59', 
    "HollowList-256": '#e34a33', "HollowList-512": '#b30000', "TestVector": "maroon",
    "HollowListv2-128": '#6baed6', "HollowListv2-256": '#2171b5',
    "HollowListv2-512": '#08306b'}
contenido = os.listdir('./CSV/')
for archivo in contenido:
    if archivo.endswith(".csv") and archivo != "sys.csv":
        df = pd.read_csv('./CSV/' + archivo)
        for test in df.TEST.unique():
            test_df = df[df.TEST == test]
            for type in test_df.TYPE.unique():
                fig, ax = plt.subplots()
                type_df = test_df[test_df.TYPE == type]
                for program in type_df.PROGRAM.unique():
                    program_df = type_df[type_df.PROGRAM == program]
                    sizes = program_df.SIZE.values
                    times = program_df.TIME.values
                    
                    # Calcula la media de los valores de 'y' cuando hay 'x' que coinciden en valor
                    unique_sizes = np.unique(sizes)
                    averaged_times = np.zeros_like(unique_sizes,dtype=np.float64)
                    for i, size in enumerate(unique_sizes):
                        averaged_times[i] = np.mean(times[sizes == size])
                    ax.plot(unique_sizes, averaged_times, label=program, 
                    color=colores[program])
                
                ax.legend()
               
                ax.set_title(f"{gen[Path(archivo).stem]} - {tests[test]} - {object[type]}")
                plt.xscale('log')
                plt.yscale('log')
                plt.xlabel('Elementos')
                plt.ylabel('Tiempo (s)')
                filename = "Todas figure_{}-{}-{}.svg".format(Path(archivo).stem, type, test)
                plt.savefig(filename, format="svg")