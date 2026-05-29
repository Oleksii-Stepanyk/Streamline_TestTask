FROM gcc:latest

RUN apt-get update && apt-get install -y python3

WORKDIR /app

COPY main.cpp .
COPY src/ ./src/
COPY include/ ./include/
COPY generate_data.py .

RUN python3 generate_data.py

RUN g++ -I include/ -O3 main.cpp src/*.cpp -o inventory_sys

ENTRYPOINT ["./inventory_sys"]
CMD ["large_inventory.csv"]