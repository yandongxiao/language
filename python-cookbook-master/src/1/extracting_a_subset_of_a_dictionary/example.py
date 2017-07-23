#!/usr/bin/env python
# encoding: utf-8

"""
    Extracting a subset of a dictionary.
"""

PRICES = {
    'ACME': 45.23,
    'AAPL': 612.78,
    'IBM': 205.55,
    'HPQ': 37.20,
    'FB': 10.75
}

# Make a dictionary of all PRICES over 200
print {key:PRICES[key] for key in PRICES if PRICES[key] > 200}
print {key:val for key, val in PRICES.items() if val > 200}
print {key:val if val > 200 else 0 for key, val in PRICES.items()}


# Make a dictionary of tech stocks
TECH_NAMES = {'AAPL', 'IBM', 'HPQ', 'MSFT'}
print {key:PRICES[key] for key in PRICES if key in TECH_NAMES}
print dict((key, PRICES[key]) for key in PRICES if key in TECH_NAMES)
