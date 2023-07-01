@mainpage README
@tableofcontents
# Logic Assignment-1
October-2022

## Credits:
| Name | Id | Mail  |
| ----: | :----: | :---- |
| Yashraj Mehta | 2020B3A72226H | f20202226@hyderabad.bits-pilani.ac.in |
| Sarvesh Sutaone | 2020B5A71947H | f20201947@hyderabad.bits-pilani.ac.in |
| Anirudh Kathera | 2020B3A71927H | f20201927@hyderabad.bits-pilani.ac.in |
| Vaishnavi Padakanti | 2020B3A70972H | f20200972@hyderabad.bits-pilani.ac.in |

@section mainsec1 How to Run?
@subsection mainsec1sub1 Inputs
- Valid Logic Expression
    + Should contain only Atoms, Operators and Brackets (No Spaces)
        + Atoms : Lower Case English Alphabets. Ex: p,q,r,s,a,b,c
        + Operators : Use only the specified Operators:
            + Conjunction ( * )
            + Disjunction ( + )
            + Implication ( > )
            + Negation ( ~ )
        + Brackets [ ( , ) ]
            + Every Sub formula MUST be enclosed by a pair of brackets
            + Enclose negation in brackets. Ex: (~(~p))
    + Examples:
        + ((p*q)>((r+s)>(~t)))
        + ((a>(~b))+(b*(~(~c))))
- Number of Propositional Atoms
    + Single Integer indicating the number of unique propositional atoms in logical expression.
- Truth Values of Propisitional Atoms
    + Single Upper Case 'T' or 'F'
        + T for True
        + F for False
    

@subsection mainsec1sub2 Outputs
- Prefix form of Entered Expression (String)
- Output of Inorder Traversal of Binary Parse Tree created (String)
- Height of the Binary Parse Tree (Integer)
- Truth Value of Expression ('T' or 'F')


@section mainsec2 Complexity Analysis

| Name | Time Complexity | n |
| ----: | :---- | :----: |
| @ref infixToPrefix | O(n<sup>2</sup>) | length of string |
| @ref makeExpressionTree | O(2<sup>n</sup>) | length of string |
| @ref inorderTraverse | O(n) | no. of nodes |
| @ref calculateHeight | O(nl) | no. of atoms * length of string |
| @ref checkTruthValue | O(2<sup>n</sup>) | no. of nodes |

@section mainsec3 Real Time Analysis


@subsection mainsec3sub1 Time taken vs. Number of Atoms
### For 3 different expressions

![](doc_images\Atom_Length.png)

@subsection mainsec3sub2 Time Taken for Different Machines

![](doc_images\Machine.png)


### Specifications for Machines Used
- Machine 1
    + Lenovo Ideapad S540
    + Processor - i5 10th Gen
    + RAM/Memory - 8GB/512GB
- Machine 2
    + Dell G7 7500
    + Processor - i7 10th Gen
    + RAM/Memory - 16GB/1TB

