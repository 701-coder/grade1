# Firewall dilemma
The firewall device in our department becomes unstable one week before the midterm exam, as described in the class today. What would you do to restore service to normal? Please explain your plan and how it can minimize the impact to the users.

我會先發公告給大家，說明防火牆出了問題，將在明天凌晨開始進行整修，預計整修到中午，整修期間會暫停系上的一些服務。然後我會盡全力儘快把防火牆修好，讓服務盡早恢復。如果很不幸的，中午前修不好，我仍會開放系統給大家用，再公告一次隔天凌晨要繼續修。我會這麼做的原因是：
1. 我沒有馬上整修，而是發公告，因為要讓使用者有充足的時間能應變
2. 我選擇明天凌晨開始整修，而不是段考完，因為不想讓使用者暴露在資安的風險中
3. 中午一定會開放給使用者是因為使用者已經按照公告的時間應變了，臨時延長整修時間會讓使用者更措手不及，而且有些作業是規定特定時間要繳交的，所以我會在說好的恢復時間恢復服務

# NTU COOL video incident
NTU COOL has lost most of the encoded video files due to an incident, as described in the class today. How do you dispatch the CPU resources to encode the video uploaded for the new semester and the old videos from previous semesters? Please explain your plan and how the plan can minimize the impact to the user.

我會先發公告給使用者，請大家儘量將新影片上傳到youtube，在cool放youtube連結，如果真的有需求才把影片上傳到cool，這樣可以大幅減少cool需要encode的新影片的量，將這些新影片encode後，剩下的CPU再拿去reencode之前的舊影片。我會這麼做的原因是：
1. 讓使用者儘量將影片上傳到youtube，雖然可能會讓他們有些不方便，但也因為並非強制的，所以不會對使用者造成太嚴重的影響。
2. 先encode新影片再reencode舊影片是因為，新影片往往比舊影片更要緊，encode新影片才能降低對使用者的影響。
