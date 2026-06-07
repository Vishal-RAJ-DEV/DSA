from typing import List
class Solution:
    def numUniqueEmails(self, emails: List[str]) -> int:
        #create a set to store the unique value 
        seen = set()

        for email in emails:
            text, domain = email.split('@')
            #split the text by + and choose the 0th index element
            #and replace all the '.' with no space 
            name = text.split('+')[0].replace('.','')
            finalemail = name + '@' + domain
            seen.add(finalemail)
        #return all the unique email 
        return len(seen)


solution = Solution()
print(solution.numUniqueEmails(["test.email+alex@leetcode.com","test.email@leetcode.com"]))