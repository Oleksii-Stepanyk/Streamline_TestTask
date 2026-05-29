import csv
import random
import time
from collections import defaultdict

BRAND_CATEGORY_OPTIONS = {
    "Nike": [
        ["T-shirts", "Clothes"],
        ["Hoodies", "Clothes"],
        ["Skirts", "Clothes"],
        ["Sneakers", "Shoes"],
        ["Running", "Shoes"],
        ["Backpacks", "Accessories"],
    ],
    "Adidas": [
        ["Hoodies", "Clothes"],
        ["Tracksuits", "Clothes"],
        ["Sneakers", "Shoes"],
        ["Soccer", "Shoes"],
        ["Socks", "Accessories"],
    ],
    "H&M": [
        ["Dresses", "Clothes"],
        ["Skirts", "Clothes"],
        ["Blouses", "Clothes"],
        ["Cardigans", "Clothes"],
        ["Tote Bags", "Accessories"],
    ],
    "Zara": [
        ["Skirts", "Clothes"],
        ["Blazers", "Clothes"],
        ["Dresses", "Clothes"],
        ["Heels", "Shoes"],
        ["Scarves", "Accessories"],
    ],
    "Timberland": [
        ["Desert", "Boots"],
        ["Work", "Boots"],
        ["Chukka", "Boots"],
        ["Belts", "Accessories"],
    ],
    "Puma": [
        ["Sneakers", "Shoes"],
        ["Running", "Shoes"],
        ["Shorts", "Clothes"],
        ["Hoodies", "Clothes"],
        ["Gym Bags", "Accessories"],
    ],
    "Reebok": [
        ["Shorts", "Clothes"],
        ["T-shirts", "Clothes"],
        ["Training", "Shoes"],
        ["Sneakers", "Shoes"],
        ["Wristbands", "Accessories"],
    ],
    "Levis": [
        ["Jeans", "Clothes"],
        ["Denim Jackets", "Clothes"],
        ["Shirts", "Clothes"],
        ["Belts", "Accessories"],
    ],
    "Gucci": [
        ["Bags", "Accessories"],
        ["Belts", "Accessories"],
        ["Loafers", "Shoes"],
        ["Sunglasses", "Accessories"],
    ],
    "Casio": [
        ["Watches", "Accessories"],
        ["G-Shock", "Watches"],
        ["Vintage", "Watches"],
    ],
}

CATEGORY_TREES = [
    [brand, *path]
    for brand, paths in BRAND_CATEGORY_OPTIONS.items()
    for path in paths
]

def generate_csv(filename: str, num_rows: int):
    root_category = "All items"
    total_warehouse_quantity = 0
    category_totals = defaultdict(int)
    category_unique_items = defaultdict(int)
    direct_subcategories = defaultdict(set)
    start_time = time.time()
    print(f"Generating {num_rows:,} rows. Please wait...")
    
    with open(filename, mode='w', newline='', encoding='utf-8') as f:
        writer = csv.writer(f)
        writer.writerow(["item_name", "quantity", "categories"])
        
        for i in range(1, num_rows + 1):
            item_name = f"item_{i:07d}"
            quantity = random.randint(1, 500)
            categories_list = random.choice(CATEGORY_TREES)
            categories_str = ",".join(categories_list)
            writer.writerow([item_name, quantity, categories_str])

            total_warehouse_quantity += quantity
            category_totals[root_category] += quantity
            category_unique_items[root_category] += 1

            parent = root_category
            for category in reversed(categories_list):
                category_totals[category] += quantity
                category_unique_items[category] += 1
                direct_subcategories[parent].add(category)
                parent = category
            direct_subcategories.setdefault(parent, set())

    stats_log_path = f"{filename}.stats.log"
    with open(stats_log_path, mode="w", encoding="utf-8") as log_file:
        log_file.write("total_warehouse_quantity=" + str(total_warehouse_quantity) + "\n")
        log_file.write("category,total_quantity,unique_items,direct_subcategories\n")
        for category in sorted(category_totals.keys()):
            subcategory_count = len(direct_subcategories.get(category, set()))
            log_file.write(
                f"{category},{category_totals[category]},"
                f"{category_unique_items[category]},{subcategory_count}\n"
            )

    end_time = time.time()
    print(f"Done! File saved as '{filename}' in {end_time - start_time:.2f} seconds.")
    print(f"Stats log saved as '{stats_log_path}'.")

if __name__ == "__main__":
    generate_csv("./data/large_inventory.csv", 1_000_000)