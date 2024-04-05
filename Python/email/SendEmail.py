# 负责发送邮件
import smtplib
# 负责构造邮件
from email.mime.multipart import MIMEMultipart
# Header 是为了能够包含非 ascii 字符，比如中文
from email.header import Header
from email.mime.text import MIMEText
from email.message import EmailMessage
from email.utils import formataddr, parseaddr

import json

def get_usr(config='config.json'):
    with open(config, 'r') as f:
        d = json.load(f)
    return d['user'], d['password'], d['send_to']

def format_addr(s:str):
    name, addr = parseaddr(s)
    return formataddr((Header(name, 'utf-8').encode(), addr))


class MakeMsg():
    def __init__(self, type:str, msg, subject:str, config:dict) -> None:
        mime_type, mime_subtype = type.lower().split('/')
        self.config = config
        if (mime_type == 'text'):
            self.m = MIMEText(msg, mime_subtype, 'utf-8')
        else:
            print('目前只支持（"text"）类型格式，暂不支持其他类型邮件。')
            exit(1)
        self.set_header(subject)
    
    def set_header(self, subject):
        self.m['From'] = format_addr(self.config["user"])
        send_to = [format_addr(addr) for addr in self.config["send_to"]]
        self.m['To'] = ', '.join(send_to)
        self.m['Subject'] = Header(subject, 'utf-8')


class SendEmail():
    
    def __init__(self, send_msg, send_config:dict) -> None:
        config = send_config
        # 连接发送邮件服务器(SSL)
        server = smtplib.SMTP_SSL('smtp.xxx.xxx', 994)
        # 打印和SMTP服务器交互的所有信息
        server.set_debuglevel(1)
        # 登录，失败会报异常
        _, user_addr = parseaddr(config["user"])
        server.login(user_addr, config["password"])
        # 构造邮件信息
        msg = send_msg
        # 发送邮件
        server.sendmail(config["user"], config["send_to"], msg.as_string())
        # 关闭邮件服务器
        server.quit()
        pass
