# 功能：替换以往提交中的涉及隐私邮箱为新的邮箱
# 用法：./fix-github-private-email.sh old-email@email.com new-email@email.com

#!/bin/bash

# 检查命令行参数数量
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <OLD_EMAIL> <NEW_EMAIL>"
    exit 1
fi

# 从命令行参数中获取旧邮箱和新邮箱
OLD_EMAIL="$1"
NEW_EMAIL="$2"

# 获取当前分支名称
CURRENT_BRANCH=$(git rev-parse --abbrev-ref HEAD)

# 获取包含私有电子邮件的所有提交哈希值
COMMITS=$(git log --format="%H" --grep=$OLD_EMAIL)

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

# 切换回当前分支
git checkout $CURRENT_BRANCH

# 恢复暂存的更改
git stash pop

# 强制推送所有修改过的提交
git push origin $CURRENT_BRANCH --force