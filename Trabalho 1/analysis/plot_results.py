import json
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import matplotlib
matplotlib.use('TkAgg')

sns.set(style="whitegrid")

def load_results(filepath):
    with open(filepath, 'r') as f:
        return json.load(f)

def analyze_fibonacci(data):
    fib_data = data['fibonacci']
    df = pd.DataFrame([{
        'n': entry['n'],
        'Iterative Time (s)': entry.get('iterative', {}).get('time', None),
        'Recursive Time (s)': entry.get('recursive', {}).get('time', None),
        'LLM Iterative Time (s)': entry.get('llm - iterative', {}).get('time', None),
        'LLM Recursive Time (s)': entry.get('llm - recursive', {}).get('time', None),
    } for entry in fib_data])

    print("\nFibonacci - Execution Time Table:")
    print(df.to_string(index=False))

    fig, axes = plt.subplots(1, 2, figsize=(14, 6), sharex=True)

    axes[0].plot(df['n'], df['Iterative Time (s)'], marker='o', label='Iterative')
    axes[0].plot(df['n'], df['Recursive Time (s)'], marker='s', label='Recursive')
    if df['LLM Iterative Time (s)'].notnull().any():
        axes[0].plot(df['n'], df['LLM Iterative Time (s)'], marker='^', label='LLM - Iterative')
    if df['LLM Recursive Time (s)'].notnull().any():
        axes[0].plot(df['n'], df['LLM Recursive Time (s)'], marker='x', label='LLM - Recursive')
    axes[0].set_title('Fibonacci Execution Time (Linear Scale)')
    axes[0].set_xlabel('Input Size (n)')
    axes[0].set_ylabel('Execution Time (seconds)')
    axes[0].grid(True, which="both", linestyle='--', linewidth=0.5)
    axes[0].legend()

    axes[1].plot(df['n'], df['Iterative Time (s)'], marker='o', label='Iterative')
    axes[1].plot(df['n'], df['Recursive Time (s)'], marker='s', label='Recursive')
    if df['LLM Iterative Time (s)'].notnull().any():
        axes[1].plot(df['n'], df['LLM Iterative Time (s)'], marker='^', label='LLM - Iterative')
    if df['LLM Recursive Time (s)'].notnull().any():
        axes[1].plot(df['n'], df['LLM Recursive Time (s)'], marker='x', label='LLM - Recursive')
    axes[1].set_title('Fibonacci Execution Time (Log Scale)')
    axes[1].set_xlabel('Input Size (n)')
    axes[1].set_ylabel('Execution Time (seconds) - log scale')
    axes[1].set_yscale('log')
    axes[1].grid(True, which="both", linestyle='--', linewidth=0.5)
    axes[1].legend()

    plt.tight_layout()
    plt.savefig('results/plots/fibonacci_execution_time_linear_vs_log.png')
    plt.show()

def analyze_polynomial(data):
    poly_data = data['polynomial']
    df = pd.DataFrame([{
        'Degree': len(entry.get('coefficients', [])) - 1,
        'Iterative Time (s)': entry.get('iterative', {}).get('time', None),
        'Recursive Time (s)': entry.get('recursive', {}).get('time', None),
        'LLM Iterative Time (s)': entry.get('llm - iterative', {}).get('time', None),
        'LLM Recursive Time (s)': entry.get('llm - recursive', {}).get('time', None),
    } for entry in poly_data])

    df = df.sort_values(by='Degree')

    print("\nPolynomial - Execution Time Table:")
    print(df.to_string(index=False))

    plt.figure(figsize=(10, 6))
    plt.plot(df['Degree'], df['Iterative Time (s)'], marker='o', label='Iterative')
    plt.plot(df['Degree'], df['Recursive Time (s)'], marker='s', label='Recursive')
    if df['LLM Iterative Time (s)'].notnull().any():
        plt.plot(df['Degree'], df['LLM Iterative Time (s)'], marker='^', label='LLM - Iterative')
    if df['LLM Recursive Time (s)'].notnull().any():
        plt.plot(df['Degree'], df['LLM Recursive Time (s)'], marker='x', label='LLM - Recursive')

    plt.title('Execution Time - Polynomial Evaluation (by Degree)')
    plt.xlabel('Polynomial Degree')
    plt.ylabel('Execution Time (seconds) - log scale')
    plt.yscale('log')
    plt.grid(True, which="both", linestyle='--', linewidth=0.5)
    plt.legend()
    plt.tight_layout()
    plt.savefig('results/plots/polynomial_execution_time.png')
    plt.show()
    
filepath = 'results/output.json'
results = load_results(filepath)
analyze_fibonacci(results)
analyze_polynomial(results)