import os
import sys
import json
import torch
import torch.nn as nn
import torch.optim as optim
from torch.utils.data import Dataset, DataLoader
import pandas as pd
import numpy as np
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score, classification_report, confusion_matrix

# PiBrain Configuration
class PiBrainConfig:
    def __init__(self):
        self.device = "cuda" if torch.cuda.is_available() else "cpu"
        self.model_type = "CNN"  # or "LSTM" or "Transformer"
        self.batch_size = 32
        self.epochs = 10
        self.learning_rate = 0.001
        self.data_path = "data/pinode_data.csv"
        self.model_path = "models/pibrain_model.pth"

# PiNode Data Loader
class PiNodeDataLoader(Dataset):
    def __init__(self, data_path):
        self.data_path = data_path
        self.data = pd.read_csv(data_path)

    def __len__(self):
        return len(self.data)

    def __getitem__(self, idx):
        data = self.data.iloc[idx]
        features = data.drop(["deviceId", "timestamp"], axis=1)
        label = data["deviceId"]
        return {
            "features": torch.tensor(features.values, dtype=torch.float),
            "label": torch.tensor(label, dtype=torch.long)
        }

# PiBrain Model
class PiBrainModel(nn.Module):
    def __init__(self, config):
        super(PiBrainModel, self).__init__()
        self.config = config
        if config.model_type == "CNN":
            self.model = nn.Sequential(
                nn.Conv1d(1, 10, kernel_size=5),
                nn.ReLU(),
                nn.MaxPool1d(kernel_size=2),
                nn.Flatten(),
                nn.Linear(10*10, 128),
                nn.ReLU(),
                nn.Linear(128, 10)
            )
        elif config.model_type == "LSTM":
            self.model = nn.LSTM(input_size=1, hidden_size=128, num_layers=1, batch_first=True)
        elif config.model_type == "Transformer":
            self.model = nn.Transformer(d_model=128, nhead=8, num_encoder_layers=6, num_decoder_layers=6)

    def forward(self, x):
        if self.config.model_type == "CNN":
            x = x.view(-1, 1, 10)
            x = self.model(x)
        elif self.config.model_type == "LSTM":
            x = x.view(-1, 1, 10)
            x, _ = self.model(x)
        elif self.config.model_type == "Transformer":
            x = x.view(-1, 10)
            x = self.model(x)
        return x

# PiBrain Trainer
class PiBrainTrainer:
    def __init__(self, config, model, data_loader):
        self.config = config
        self.model = model
        self.data_loader = data_loader
        self.criterion = nn.CrossEntropyLoss()
        self.optimizer = optim.Adam(model.parameters(), lr=config.learning_rate)

    def train(self):
        for epoch in range(self.config.epochs):
            for batch in self.data_loader:
                features, labels = batch
                features = features.to(self.config.device)
                labels = labels.to(self.config.device)
                self.optimizer.zero_grad()
                outputs = self.model(features)
                loss = self.criterion(outputs, labels)
                loss.backward()
                self.optimizer.step()
            print(f"Epoch {epoch+1}, Loss: {loss.item()}")

    def evaluate(self):
        self.model.eval()
        test_loss = 0
        correct = 0
        with torch.no_grad():
            for batch in self.data_loader:
                features, labels = batch
                features = features.to(self.config.device)
                labels = labels.to(self.config.device)
                outputs = self.model(features)
                loss = self.criterion(outputs, labels)
                test_loss += loss.item()
                _, predicted = torch.max(outputs, 1)
                correct += (predicted == labels).sum().item()
        accuracy = correct / len(self.data_loader.dataset)
        print(f"Test Loss: {test_loss / len(self.data_loader)}")
        print(f"Test Accuracy: {accuracy:.2f}%")

# Main Function
def main():
    config = PiBrainConfig()
    data_loader = PiNodeDataLoader(config.data_path)
    model = PiBrainModel(config)
    trainer = Pi
trainer = PiBrainTrainer(config, model, data_loader)

# Train the model
trainer.train()

# Evaluate the model
trainer.evaluate()

# Save the model
torch.save(model.state_dict(), config.model_path)

# Load the model
def load_model(config):
    model = PiBrainModel(config)
    model.load_state_dict(torch.load(config.model_path))
    return model

# Use the model for inference
def infer(device_id, data):
    config = PiBrainConfig()
    model = load_model(config)
    model.eval()
    data = torch.tensor(data, dtype=torch.float)
    output = model(data)
    _, predicted = torch.max(output, 1)
    return predicted.item()

# MQTT Client for receiving data from PiNodes
import paho.mqtt.client as mqtt

def on_message(client, userdata, message):
    data = json.loads(message.payload)
    device_id = data["deviceId"]
    data = data["data"]
    prediction = infer(device_id, data)
    print(f"Received data from {device_id}, Prediction: {prediction}")

def on_connect(client, userdata, flags, rc):
    print("Connected to MQTT broker")
    client.subscribe("PiSphere/data")

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message
client.connect("mqtt_broker_ip", 1883)
client.loop_forever()
