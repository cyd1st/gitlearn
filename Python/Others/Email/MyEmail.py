import smtplib
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
from email.mime.application import MIMEApplication
from email.mime.image import MIMEImage
from email.mime.base import MIMEBase
from email import encoders
import json
import logging

# 设置日志记录
logging.basicConfig(level=logging.DEBUG, format='%(message)s')

class EmailClient:
    msg: MIMEMultipart
    def __init__(self, config_file='config.json'):
        # 加载配置文件
        with open(config_file, 'r') as f:
            self.config = json.load(f)
        
        # 初始化SMTP服务器连接
        self.smtp_server = self.config['smtp_server_ssl']
        self.smtp_port = int(self.config['smtp_server_ssl_port'])
        self.user = self.config['user']
        self.password = self.config['password']
        self.recipients = self.config['send_to']
        self.server = None
    
    def _connect(self):
        """ 连接到SMTP服务器 """
        self.server = smtplib.SMTP_SSL(self.smtp_server, self.smtp_port)
        # self.server.set_debuglevel(1) # 打印和SMTP服务器交互的所有信息
        logging.info("Connected to server.")
        self.server.login(self.user.split()[1][1:-1], self.password)
        logging.info("Logged in.")

    def create_message(self, subject, body, attachments=None, html=False):
        """
        创建邮件消息对象
        :param subject: 邮件主题
        :param body: 邮件正文
        :param attachments: 附件列表 (路径列表)
        :param html: 是否为HTML格式
        :return: MIMEMultipart 对象
        """
        self.msg = MIMEMultipart()
        self.msg['From'] = self.user
        self.msg['To'] = ', '.join(self.recipients)  # 多个收件人用逗号分隔
        self.msg['Subject'] = subject

        if html:
            part = MIMEText(body, 'html')
        else:
            part = MIMEText(body, 'plain')
        self.msg.attach(part)

        # 添加附件
        if attachments:
            for attachment in attachments:
                with open(attachment, 'rb') as file:
                    part = MIMEBase('application', 'octet-stream')
                    part.set_payload(file.read())
                    encoders.encode_base64(part)
                    part.add_header('Content-Disposition', 'attachment', filename=attachment)
                    self.msg.attach(part)

    def send(self, msg=None):
        """ 发送邮件 """
        self._connect()

        if  not msg:
            msg = self.msg
        try:
            self.server.sendmail(self.user.split()[1][1:-1], self.recipients, msg.as_string())
            logging.info("Email sent successfully.")
        except Exception as e:
            logging.error("Failed to send the email.")
            logging.error(str(e))
        finally:
            self.server.quit()
            logging.info("Disconnected from server.")

def TestCase1():
    email_client = EmailClient()
    subject = 'Hello'
    body = '<h1>Hello World!</h1>'  # 可以是纯文本或HTML
    # attachments = ['path/to/file.pdf', 'path/to/image.png']  # 附件列表
    email_client.create_message(subject, body, html=True)
    email_client.send()

# 使用示例
if __name__ == '__main__':
    TestCase1()