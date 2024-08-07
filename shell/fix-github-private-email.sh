#!/bin/bash

# 设置新的电子邮件地址
NEW_EMAIL="43594415+cyd1st@users.noreply.github.com"

# 获取包含私有电子邮件的所有提交哈希值
COMMITS=$(git log --format="%H" --grep="cyd1997@126.com")

# 暂存当前工作目录中的更改
git stash save "Temporarily stashed changes"

# 循环遍历每个提交
for COMMIT in $COMMITS; do
    # 回滚到指定的提交
    git checkout $COMMIT
   
    # 修改提交的作者信息
    git commit --amend --no-edit --author="Your Name <$NEW_EMAIL>"
   
    # 打印出修改的提交
    echo "Modified commit $COMMIT"
done

# 回到 HEAD，即最新的提交
# git checkout main

# 恢复暂存的更改
git stash pop

# 强制推送所有修改过的提交
git push origin main --force