import pandas as pd
import matplotlib.pyplot as plt
import os

def generar_graficos():
    base_dir = os.path.dirname(os.path.abspath(__file__))
    csv_path = os.path.join(base_dir, "..", "measurements", "sorting", "sorting_measurements.csv")
    if not os.path.exists(csv_path):
        csv_path = os.path.join(base_dir, "..", "..", "..", "measurements", "sorting", "sorting_measurements.csv")
    
    out_dir = os.path.join(base_dir, "..", "data", "plots")
    os.makedirs(out_dir, exist_ok=True)

    df = pd.read_csv(csv_path)
    # Promediar las muestras (a, b, c) por algoritmo, n, tipo y dominio
    df_avg = df.groupby(['algoritmo', 'n', 'tipo', 'dominio'])['tiempo_segundos'].mean().reset_index()

    for tipo in df_avg['tipo'].unique():
        for dom in df_avg['dominio'].unique():
            plt.figure(figsize=(9, 6))
            sub_df = df_avg[(df_avg['tipo'] == tipo) & (df_avg['dominio'] == dom)]
            
            for algo in sub_df['algoritmo'].unique():
                data_algo = sub_df[sub_df['algoritmo'] == algo].sort_values('n')
                plt.plot(data_algo['n'], data_algo['tiempo_segundos'], marker='o', label=algo)

            plt.xscale('log')
            plt.yscale('log')
            plt.xlabel('Tamaño del Arreglo (n)')
            plt.ylabel('Tiempo Promedio (segundos)')
            plt.title(f'Sorting: Tiempo vs n ({tipo} - {dom})')
            plt.grid(True, which="both", ls="--", alpha=0.5)
            plt.legend()
            
            plot_file = os.path.join(out_dir, f'plot_{tipo}_{dom}.png')
            plt.savefig(plot_file, dpi=300, bbox_inches='tight')
            plt.close()
            print(f"Gráfico guardado: {plot_file}")

if __name__ == "__main__":
    generar_graficos()