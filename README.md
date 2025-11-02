
# 🛰️ Carbon Intensity Monitoring & Alerting System

**Language:** C
**Libraries:** libcurl, JSON
**Automation Tools:** Cron, SMTP
**Platform:** Linux

---

## 📖 Overview

This project automates the **fetching, processing, and analysis of real-time carbon intensity data** using the **Carbon Intensity API**.
It computes environmental metrics such as average, median, and standard deviation of carbon intensity, generates weekly reports, and automatically sends **email alerts** when carbon levels exceed predefined thresholds.
The entire workflow runs autonomously through **cron jobs**, ensuring scheduled execution, data consistency, and secure alert notifications via **SMTP**.

---

## 🧩 File Structure

| File                  | Description                                                                                                                                   |
| --------------------- | --------------------------------------------------------------------------------------------------------------------------------------------- |
| **main_code.c**       | Main driver program. Fetches real-time data from the Carbon Intensity API using libcurl and integrates data processing functions.             |
| **data_processing.c** | Contains functions for parsing JSON data, calculating metrics (average, median, standard deviation), and generating daily and weekly reports. |
| **email_logs.h**      | Handles SMTP configuration, logging, and email composition for automated alert notifications.                                                 |

---

## ⚙️ Features

### 🔹 Data Retrieval & Processing

* Fetches live carbon intensity data through **libcurl**.
* Parses JSON responses to extract values and calculate environmental metrics.
* Stores processed results locally for daily and weekly analysis.

### 🔹 Automated Reporting & Alerts

* Generates detailed daily and weekly reports summarizing carbon intensity trends.
* Sends **automated email alerts** to stakeholders when critical thresholds are breached.
* Implements robust **logging and error handling** for reliable performance.

### 🔹 Automation & Scheduling

* Utilizes **cron jobs** to automatically execute daily and weekly tasks.
* Performs **directory management and cleanup** to maintain efficient storage.
* Ensures **data integrity** with exception handling during automated runs.

---

## 🧰 Dependencies

To compile and run this project, ensure the following are installed on your system:

* **libcurl** → For making HTTP requests to the API.
* **json-c** → For parsing JSON data.
* **time.h**, **stdio.h**, **string.h** → Standard C libraries for file I/O and time handling.
* **SMTP server access** → Required for sending automated alert emails.

---

## 🛠️ Installation

### 1. Clone the repository

```bash
git clone https://github.com/yourusername/carbon-intensity-monitor.git
cd carbon-intensity-monitor
```

### 2. Install dependencies

For Debian/Ubuntu systems:

```bash
sudo apt-get update
sudo apt-get install libcurl4-openssl-dev libjson-c-dev
```

### 3. Configure SMTP

Edit the `email_logs.h` file to include your email credentials and SMTP server details:

```c
#define SMTP_SERVER "smtp.yourmail.com"
#define SMTP_PORT 587
#define SMTP_USER "your_email@example.com"
#define SMTP_PASS "your_password"
```

---

## 🚀 Usage

### 🔸 Compile the code

```bash
gcc main_code.c data_processing.c -lcurl -ljson-c -o carbon_monitor
```

### 🔸 Run manually

```bash
./carbon_monitor
```

### 🔸 Automate with cron (Linux)

Set up scheduled runs for daily and weekly analysis:

```bash
crontab -e
```

Add the following lines:

```bash
0 8 * * * /path/to/carbon_monitor        # Runs daily at 8 AM
0 18 * * 7 /path/to/carbon_monitor       # Runs weekly every Sunday at 6 PM
```

---

## 📡 Distinguishing Features

* **Modular design:** Separate C modules for API handling, data processing, and email notifications.
* **Full automation:** End-to-end automation from data retrieval to alert generation.
* **Logging system:** Captures key events, errors, and alerts for auditing.
* **Security focus:** Implements secure data handling and SMTP authentication.
* **Scalable:** Easily extendable for new APIs or predictive analytics integration.

---

## 🧠 Future Enhancements

* Integrate **machine learning algorithms** for predictive carbon trend forecasting.
* Add **interactive dashboards** for visual data representation.
* Improve compatibility with multiple APIs and mail servers.
* Include **encryption** for email alerts to enhance data confidentiality.

---

## 🛠️ Problems Faced

* Difficulties integrating with third-party APIs using `libcurl`.
* Compatibility issues with varying SMTP servers and configurations.
* Cron job setup challenges for reliable background execution and log monitoring.

---

## 📊 Outputs

### ✅ Terminal Output

Displays real-time fetched data, calculated statistics, and execution logs.

### 🧾 Weekly Report

Includes average, median, and standard deviation of carbon intensity values.

### 📧 Email Notification

Automatically sends threshold alerts with detailed metric summaries to configured recipients.

---

## 🧱 Example Workflow

```bash
1️⃣ Fetch data from Carbon Intensity API → 
2️⃣ Parse and process JSON response → 
3️⃣ Generate daily/weekly reports → 
4️⃣ Trigger SMTP-based email alerts (if thresholds exceeded) → 
5️⃣ Automate future executions using cron jobs.
```

---

## 📂 Project Directory Structure

```
carbon-intensity-monitor/
│
├── main_code.c           # Fetches data and controls overall workflow
├── data_processing.c     # Handles analysis, metrics, and report generation
├── email_logs.h          # SMTP configuration and logging
├── reports/              # Generated reports (daily/weekly)
├── logs/                 # Execution and error logs
└── README.md             # Project documentation
```

---

## 💡 Project Members:

**Sehrish Ahmed Sangrasi**
**Laiba Mushtaq**
**Hiba Fatima**
*Computer Systems Engineering, NED University of Engineering & Technology*

---

## 🏁 License

This project is developed for academic and research purposes.
Feel free to modify and expand it for non-commercial educational use.


