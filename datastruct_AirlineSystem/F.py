import random

# 定义飞机型号及对应额定座位数
plane_capacity = {
    'A320': 180,
    'B737': 162,
    'A330': 300,
    'B777': 366,
    'A350': 314,
    'B787': 290,
    'A220': 135,
    'CRJ900': 90
}

# 定义可能的选项
destinations = ['Shanghai', 'Beijing', 'Guangzhou', 'Shenzhen', 'Chengdu',
                'Hangzhou', 'Nanjing', 'Xi\'an', 'Wuhan', 'Chongqing']
airlines = ['CA', 'MU', 'CZ', 'HU', 'SC', '9C', '3U', 'BK', 'G5', 'KY']
plane_models = list(plane_capacity.keys())

# 生成2024年的日期，不考虑闰年，假设2月有28天
dates = [f'2024{str(month).zfill(2)}{str(day).zfill(2)}' for month in range(1, 3) for day in range(1, 31) if not (month == 2 and day > 28)]

num_flights = 200  # 生成200条航班数据

with open('flight.txt', 'w') as f:
    for _ in range(num_flights):
        dest = random.choice(destinations)
        airline = random.choice(airlines)
        flight_no = f'{airline}{random.randint(100,999)}'
        plane_model = random.choice(plane_models)
        rated_seats = plane_capacity[plane_model]
        date = random.choice(dates)
        # 30%的概率生成满员航班
        if _ % 5 == 0:
            remaining_seats = 0
        else:
            remaining_seats = random.randint(0, rated_seats)
        f.write(f'{dest} {flight_no} {plane_model} {date} {rated_seats} {remaining_seats}\n')