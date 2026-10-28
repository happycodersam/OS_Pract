import numpy as np 
import pandas as pd 
from sklearn.datasets import load_breast_cancer 
from sklearn.model_selection import train_test_split 
from sklearn.preprocessing import StandardScaler 
from sklearn.linear_model import LogisticRegression 
from sklearn.neighbors import KNeighborsClassifier 
from sklearn.metrics import accuracy_score, precision_score, recall_score, f1_score, confusion_matrix

data = load_breast_cancer() 
X = data.data 
y = data.target

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42, stratify=y)

scaler = StandardScaler() 
X_train = scaler.fit_transform(X_train) 
X_test = scaler.transform(X_test)

logistic_model = LogisticRegression(max_iter=1000) 
logistic_model.fit(X_train, y_train) 
y_pred_logistic = logistic_model.predict(X_test)

accuracy_logistic = accuracy_score(y_test, y_pred_logistic) 
precision_logistic = precision_score(y_test, y_pred_logistic) 
recall_logistic = recall_score(y_test, y_pred_logistic) 
f1_logistic = f1_score(y_test, y_pred_logistic) 
cm_logistic = confusion_matrix(y_test, y_pred_logistic)

knn_model = KNeighborsClassifier(n_neighbors=5) 
knn_model.fit(X_train, y_train) 
y_pred_knn = knn_model.predict(X_test)

accuracy_knn = accuracy_score(y_test, y_pred_knn) 
precision_knn = precision_score(y_test, y_pred_knn) 
recall_knn = recall_score(y_test, y_pred_knn) 
f1_knn = f1_score(y_test, y_pred_knn) 
cm_knn = confusion_matrix(y_test, y_pred_knn)

print("LOGISTIC REGRESSION") 
print("Accuracy:", accuracy_logistic) 
print("Precision:", precision_logistic) 
print("Recall:", recall_logistic) 
print("F1-Score:", f1_logistic) 
print("Confusion Matrix:\n", cm_logistic)

print("\nK-NEAREST NEIGHBORS (KNN)") 
print("Accuracy:", accuracy_knn) 
print("Precision:", precision_knn) 
print("Recall:", recall_knn) 
print("F1-Score:", f1_knn) 
print("Confusion Matrix:\n", cm_knn)
