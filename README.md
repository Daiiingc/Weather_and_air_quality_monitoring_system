# Weather and air quality monitoring system
Xây dựng một hệ thống thu nhập dữ liệu từ các cảm biến môi trường như nhiệt độ, độ ẩm, nồng độ khí CO2, dữ liệu thu được sẽ lưu trên cơ sở dữ liệu thời gian thực InfluxDB và trực quan hoá dữ liệu trên nền tảng Grafana.

Hệ thống được xây dựng nhằm mục đích ta quan sát các giá trị dữ liệu theo thời gian thực dựa trên các biểu đồ hình, từ đó ta có thể giám sát hệ thống từ xa, đánh giá các thông số đó theo các khoảng thời gian và đưa ra một số thông tin cần thiết về thời tiết và chất lượng không khí.

Video demo: [video_demo](https://youtu.be/qplAFM0V6wE)

## Phần cứng sử dụng
- ESP32
- Raspberry Pi
- DHT11
- MQ135

## Phần mềm sử dụng
- Vscode 
- Platform.io
- Cơ sở dữ liệu thời gian thực InfluxDB
- Nền tảng Grafana

## Sơ đồ khối

<img src = "https://github.com/Daiiingc/Weather_and_air_quality_monitoring_system/blob/main/image/so_do_khoi.png">

## Giới thiệu phần mềm
### Grafana
Grafana là một nền tảng mã nguồn mở được sử dụng để giám sát, phân tích và trực quan hóa dữ liệu trong thời gian thực thông qua các bảng điều khiển (dashboards). Cụ thể, nó là một vizualizer hiển thị các metric dưới dạng các biểu đồ (chart) hoặc đồ thị (graph), được tập hợp lại thành dashboard có tính tùy biến cao, giúp dễ dàng theo dõi tình trạng của các thông tin mình truy nhập đến.

Ta có thể hiểu đơn giản là sau khi lấy được thông tin số liệu từ các thiết bị, Grafana sẽ sử dụng các dữ liệu đó để phân tích và tạo ra dashboard mô tả trực quan các thông tin số liệu cần thiết cho việc điều khiển, giám sát. Grafana là một nền tảng nằm trên lớp ứng dụng người dùng của hệ thống IoT. 

Cài đặt Grafana trên Raspberry Pi 3: [link](https://github.com/Daiiingc/Weather_and_air_quality_monitoring_system/blob/main/c%C3%A0i%20%C4%91%E1%BA%B7t%20Grafana%20tr%C3%AAn%20raspberry%20pi.txt)

### InfluxDB
InfluxDB là một cơ sở dữ liệu chuỗi thời gian mã nguồn mở (TSDB) do InfluxData phát triển. Cơ sở dữ liệu này được tối ưu hóa để lưu trữ và truy xuất dữ liệu chuỗi thời gian nhanh chóng, có tính ứng dụng cao trong các lĩnh vực như giám sát hoạt động, dữ liệu hiệu suất ứng dụng, dữ liệu cảm biến IoT và phân tích thời gian thực. Grafana có hỗ trợ tích hợp cho InfluxDB.

Cài đặt InfluxDB trên Raspberry Pi 3: [link](https://github.com/Daiiingc/Weather_and_air_quality_monitoring_system/blob/main/c%C3%A0i%20%C4%91%E1%BA%B7t%20InfluxDB%20tr%C3%AAn%20raspberry%20pi.txt)

## Code ESP32
Ta sử dụng ESP32 để code đọc các cảm biến như DHT11 và MQ135, đoạn code có sử dụng các thư viện có sẵn.
Sau đó, ta code phần đoạn kết nối ESP32 đến cơ sở dữ liệu InfluxDB sử dụng thư viện của cơ sở dữ liệu đó để gửi dữ liệu cảm biến, sử dụng giao thức HTTP để gửi dữ liệu.

Đoạn code được mô tả trong Folder: [Code](https://github.com/Daiiingc/Weather_and_air_quality_monitoring_system/tree/main/weather_monitor)

## Thiết kế dashboard trên nền tảng Grafana
Qua việc tìm hiểu và tham khảo các dashboard, ta xây dựng một mẫu thiết kế bảng biểu đồ dữ liệu theo ý muốn của bản thân. Trong mỗi bảng biểu đồ, sử dụng câu lệnh truy vấn để lấy các thông tin dữ liệu riêng biệt và trực quan hoá trên biểu đồ. Các biểu đồ được tập hợp và gom lại để tạo nên một dashboard

<img src = "https://github.com/Daiiingc/Weather_and_air_quality_monitoring_system/blob/main/image/dashboard.png">

