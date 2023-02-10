echo "repo link"
read link

git init

git add .

git commit -m "firstCommit"

git remote add origin $link

git push -u origin master
