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
        'LLM Time (s)': entry.get('llm', {}).get('time', None),
    } for entry in fib_data])

    print("\nFibonacci - Execution Time Table:")
    print(df.to_string(index=False))

    plt.figure(figsize=(10,6))
    if 'Iterative Time (s)' in df.columns:
        plt.plot(df['n'], df['Iterative Time (s)'], marker='o', label='Iterative')
    if 'Recursive Time (s)' in df.columns:
        plt.plot(df['n'], df['Recursive Time (s)'], marker='s', label='Recursive')
    if 'LLM Time (s)' in df.columns and df['LLM Time (s)'].notnull().any():
        plt.plot(df['n'], df['LLM Time (s)'], marker='^', label='LLM')

    plt.title('Fibonacci - Execution Time vs Input Size (n)')
    plt.xlabel('Input Size (n)')
    plt.ylabel('Execution Time (seconds)')
    plt.yscale('log') 
    plt.legend()
    plt.tight_layout()
    plt.show()

def analyze_polynomial(data):
    poly_data = data['polynomial']
    df = pd.DataFrame([{
        'x': entry['x'],
        'Iterative Time (s)': entry.get('iterative', {}).get('time', None),
        'Recursive Time (s)': entry.get('recursive', {}).get('time', None),
        'LLM Time (s)': entry.get('llm', {}).get('time', None),
    } for entry in poly_data])

    print("\nPolynomial - Execution Time Table:")
    print(df.to_string(index=False))

    plt.figure(figsize=(10,6))
    width = 0.2
    x_positions = range(len(df))

    if 'Iterative Time (s)' in df.columns:
        plt.bar([x - width for x in x_positions], df['Iterative Time (s)'], width=width, label='Iterative')
    if 'Recursive Time (s)' in df.columns:
        plt.bar(x_positions, df['Recursive Time (s)'], width=width, label='Recursive')
    if 'LLM Time (s)' in df.columns and df['LLM Time (s)'].notnull().any():
        plt.bar([x + width for x in x_positions], df['LLM Time (s)'], width=width, label='LLM')

    plt.title('Polynomial - Execution Time Comparison')
    plt.xlabel('Input x (Index)')
    plt.ylabel('Execution Time (seconds)')
    plt.xticks(ticks=x_positions, labels=[f'x={x}' for x in df['x']])
    plt.legend()
    plt.tight_layout()
    plt.show()
    

filepath = 'results/output.json'
results = load_results(filepath)
analyze_fibonacci(results)
analyze_polynomial(results)