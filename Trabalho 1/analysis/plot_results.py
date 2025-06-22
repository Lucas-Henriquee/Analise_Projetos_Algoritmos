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

    plt.figure(figsize=(10, 6))
    plt.plot(df['n'], df['Iterative Time (s)'], marker='o', label='Iterative')
    plt.plot(df['n'], df['Recursive Time (s)'], marker='s', label='Recursive')
    if df['LLM Iterative Time (s)'].notnull().any():
        plt.plot(df['n'], df['LLM Iterative Time (s)'], marker='^', label='LLM - Iterative')
    if df['LLM Recursive Time (s)'].notnull().any():
        plt.plot(df['n'], df['LLM Recursive Time (s)'], marker='x', label='LLM - Recursive')

    plt.title('Execution Time - Fibonacci (Iterative vs Recursive vs LLM)')
    plt.xlabel('Input Size (n)')
    plt.ylabel('Execution Time (seconds)')
    plt.yscale('log')
    plt.grid(True, which="both", linestyle='--', linewidth=0.5)
    plt.legend()
    plt.tight_layout()
    plt.savefig('results/plots/fibonacci_execution_time.png')
    plt.show()

def analyze_polynomial(data):
    poly_data = data['polynomial']
    df = pd.DataFrame([{
        'x': entry['x'],
        'Iterative Time (s)': entry.get('iterative', {}).get('time', None),
        'Recursive Time (s)': entry.get('recursive', {}).get('time', None),
        'LLM Iterative Time (s)': entry.get('llm - iterative', {}).get('time', None),
        'LLM Recursive Time (s)': entry.get('llm - recursive', {}).get('time', None),
    } for entry in poly_data])

    print("\nPolynomial - Execution Time Table:")
    print(df.to_string(index=False))

    plt.figure(figsize=(10, 6))
    plt.plot(df['x'], df['Iterative Time (s)'], marker='o', label='Iterative')
    plt.plot(df['x'], df['Recursive Time (s)'], marker='s', label='Recursive')
    if df['LLM Iterative Time (s)'].notnull().any():
        plt.plot(df['x'], df['LLM Iterative Time (s)'], marker='^', label='LLM - Iterative')
    if df['LLM Recursive Time (s)'].notnull().any():
        plt.plot(df['x'], df['LLM Recursive Time (s)'], marker='x', label='LLM - Recursive')

    plt.title('Execution Time - Polynomial Evaluation (Iterative vs Recursive vs LLM)')
    plt.xlabel('Input x Value')
    plt.ylabel('Execution Time (seconds)')
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