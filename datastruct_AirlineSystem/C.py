import random
from faker import Faker

# 安装Faker库以生成假数据
# !pip install faker

fake = Faker('zh_CN')  # 生成中文名字

# 读取flight.txt中的数据
flights = {}
with open('flight.txt', 'r') as f:
    for line in f:
        data = line.strip().split()
        dest, flight_no, plane_model, date, rated_seats, remaining_seats = data
        flights[(flight_no, plane_model, date)] = {
            'rated_seats': int(rated_seats),
            'remaining_seats': int(remaining_seats)
        }

# 生成成功购票的客户数据
customers = []
for flight, info in flights.items():
    flight_no, plane_model, date = flight
    sold_seats = info['rated_seats'] - info['remaining_seats']
    seats_left = sold_seats
    while seats_left > 0:
        tickets = random.randint(1, min(3, seats_left))
        name = fake.name()
        cabin = random.choice(['1', '2','3'])
        is_waiting = '0'  # 成功购票
        customers.append(f'{name} {cabin} {tickets} {flight_no} {plane_model} {date} {is_waiting}')
        seats_left -= tickets

# 找出剩余座位为0的航班，并生成候补客户的购票数据
full_flights = [flight for flight, info in flights.items() if info['remaining_seats'] == 0]
print(f"Number of full flights: {len(full_flights)}")
for flight in full_flights:
    flight_no, plane_model, date = flight
    num_waiting = random.randint(20, 50)
    print(f"Generating {num_waiting} waiting customers for flight {flight_no}")
    for _ in range(num_waiting):
        tickets = random.randint(1, 3)
        name = fake.name()
        cabin = random.choice(['1', '2','3'])
        is_waiting = '1'  # 候补
        customers.append(f'{name} {cabin} {tickets} {flight_no} {plane_model} {date} {is_waiting}')

# 将所有客户数据写入customers.txt
with open('customers.txt', 'w') as f:
    for customer in customers:
        f.write(customer + '\n')