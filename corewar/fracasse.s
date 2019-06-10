.name		"fracasse"
.comment	"un cerveau des plus ravages"

st		r1, -50
st		r1, -100
ld		%60, r5
ld		%60, r6
ld		%60, r3
prep:		ld		%58, r4
ld		%1, r2
sti		r2, r3, %0
sti		r1, r4, %0
sti		r2, %:prep, %-1
sti		r1, %:prep, %3
add		r5, r3, r3
add		r6, r4, r4
fork	%:prep
fork	%10
fork	%:prep
fork	%10
