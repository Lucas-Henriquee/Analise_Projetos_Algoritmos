import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import os

ARQUIVO_DE_DADOS = 'output/results.csv'
DIRETORIO_SAIDA = 'analise_graficos_comparativos'

def carregar_dados(caminho_arquivo):

    try:
        df = pd.read_csv(caminho_arquivo)
        df['tempo_execucao_us'] = df['execution_time_us'] 
        df['V_mais_E'] = df['num_vertices'] + df['num_edges']
        df['Tipo'] = df['is_directed'].apply(lambda x: 'Direcionado' if x == 1 else 'Não Direcionado')
        df['Conectividade'] = df['is_connected'].apply(lambda x: 'Conexo' if x == 1 else 'Desconexo')
        
        print("Dados carregados com sucesso!")
        print(df.head().to_string())
        return df
        
    except FileNotFoundError:
        print(f"Erro: O arquivo '{caminho_arquivo}' não foi encontrado.")
        print("Certifique-se de executar o script 'exec_all.sh' primeiro.")
        return None

def gerar_tabelas_resumo(df):

    if df is None: return
    if not os.path.exists(DIRETORIO_SAIDA): os.makedirs(DIRETORIO_SAIDA)
    
    caminho_tabela_geral = os.path.join(DIRETORIO_SAIDA, 'tabela_geral_completa.csv')
    df.to_csv(caminho_tabela_geral, index=False, float_format='%.6f', encoding='utf-8')
    print(f"\nTabela geral completa salva em: '{caminho_tabela_geral}'")

    grouping_cols = ['Tipo', 'Conectividade']
    if 'versao_algoritmo' in df.columns:
        grouping_cols.insert(0, 'versao_algoritmo')

    tabela_resumo = df.groupby(grouping_cols)['tempo_execucao_us'].agg(['mean', 'median', 'std', 'count']).round(4)
    tabela_resumo.columns = ['Média (us)', 'Mediana (us)', 'Desvio Padrão', 'Contagem']
    
    print("\n--- Tabela de Resumo ---")
    print(tabela_resumo)
    
    caminho_tabela_resumo = os.path.join(DIRETORIO_SAIDA, 'tabela_resumo_comparativo.csv')
    tabela_resumo.to_csv(caminho_tabela_resumo, float_format='%.4f', encoding='utf-8')
    print(f"Tabela de resumo salva em: '{caminho_tabela_resumo}'")


def gerar_graficos(df):

    if df is None: return
    sns.set_theme(style="whitegrid", palette="colorblind")

    is_comparative = 'versao_algoritmo' in df.columns
    hue_param = 'versao_algoritmo' if is_comparative else None
    
    plt.figure(figsize=(12, 7))
    sns.scatterplot(data=df, x='V_mais_E', y='tempo_execucao_us', hue=hue_param,
                    alpha=0.8, s=80)
    plt.xscale('log')
    plt.yscale('log')
    title = 'Comparativo de Performance' if is_comparative else 'Análise de Performance'
    plt.title(f'{title}: Tamanho da Instância vs. Tempo de Execução', fontsize=16, pad=20, fontweight="bold")
    plt.xlabel('Tamanho da Instância (V + E) - Escala Log', fontsize=12)
    plt.ylabel('Tempo de Execução (us) - Escala Log', fontsize=12)
    if is_comparative:
        plt.legend(title='Versão do Algoritmo')
    plt.grid(True, which="both", ls="--", linewidth=0.5)
    plt.tight_layout()
    plt.savefig(os.path.join(DIRETORIO_SAIDA, 'grafico_performance_dispersao.png'))
    plt.show()



    g = sns.catplot(
        data=df, x='Tipo', y='tempo_execucao_us',
        hue=hue_param, col='Conectividade',
        kind='bar', errorbar=None,
        height=8, aspect=1.1,
        palette='magma'
    )
    g.fig.suptitle('Análise de Tempo Médio por Categoria', fontsize=19, fontweight="bold")
    g.set_axis_labels("Tipo de Grafo", "Tempo Médio de Execução (us)")
    g.set_titles("Grafos do Tipo: {col_name}")
    
    if is_comparative:
        legend_title = g.legend.get_title().get_text()
        g.legend.remove()
        g.axes.flat[-1].legend(loc='upper right', title=legend_title)
        
    plt.yscale('log')    
    plt.tight_layout(rect=[0, 0, 1, 0.97])
    plt.savefig(os.path.join(DIRETORIO_SAIDA, 'grafico_analise_categorias.png'))
    plt.show()
    
    print(f"Gráficos salvos no diretório '{DIRETORIO_SAIDA}'")

df_resultados = carregar_dados(ARQUIVO_DE_DADOS)

if df_resultados is not None:
    gerar_tabelas_resumo(df_resultados)
    gerar_graficos(df_resultados)
