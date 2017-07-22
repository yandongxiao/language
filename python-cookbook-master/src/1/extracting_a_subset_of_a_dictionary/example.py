#!/usr/bin/env python
# encoding: utf-8


prices = {
    'ACME': 45.23,
    'AAPL': 612.78,
    'IBM': 205.55,
    'HPQ': 37.20,
    'FB': 10.75
}

# Make a dictionary of all prices over 200
print {key:prices[key] for key in prices if prices[key] > 200}
print {key:val for key, val in prices.items() if val > 200}
print {key:val if val > 200 else 0 for key, val in prices.items()}


# Make a dictionary of tech stocks
tech_names = { 'AAPL', 'IBM', 'HPQ', 'MSFT' }
print {key:prices[key] for key in prices if key in tech_names}
print dict((key, prices[key]) for key in prices if key in tech_names)
