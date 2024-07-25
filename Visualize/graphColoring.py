from manim import *

class Array(Scene):
	def getArray(self,array):
		resultArray=VGroup()
		resultArray.add(self.getBox(array[0],ManimColor.from_hsv([array[0]/max(array),1,255])))

		for i in range(1,len(array)):
			box=self.getBox(array[i],ManimColor.from_hsv([array[i]/max(array),1,255]))
			box.shift(RIGHT*i)
			resultArray.add(box)
		
		resultArray.move_to((0,0,0))
		
		return resultArray

	def getBox(self,text,textColor):
		result=VGroup()

		box=Square(side_length=1,color=GRAY)
		text=Text(str(text),color=textColor).move_to(box.get_center())

		result.add(box,text)
		return result
	
	def getIndices(self,array,startNum):
		indices=VGroup()

		for i in range(len(array)):
			text=Text(str(i+startNum),font_size=20).next_to(array[i],UP)
			indices.add(text)

		return indices

class GCP(Scene):
	def construct(self):
		vertices = [1,2,3,4,5]
		edges = [(1,2),(1,4),(2,3),(2,4),(2,5),(3,5),(4,5)]
		graph = Graph(vertices,edges,layout={1:[0,0,0],2:[3,0,0],3:[6,0,0],4:[1.5,-1.5,0],5:[4.5,-1.5,0]},labels=True)

		graph.move_to([0,0,0])
		self.play(FadeIn(graph),run_time=2)
		self.wait(0.5)
		self.play(graph.animate.to_edge(UP),run_time=2)
		self.wait(0.5)
		
		c1 = [1,2,1,3,4]
		c2 = [1,2,2,1,3]
		c3 = [1,2,3,3,1]

		color1 = self.getSequence(c1)
		color2 = self.getSequence(c2)
		color3 = self.getSequence(c3)

		c1Label = MathTex("Col1",":")
		c1Label.next_to(color1,LEFT)

		color1.add(c1Label)

		c2Label = MathTex("Col2",":")
		c2Label.next_to(color2,LEFT)
		
		color2.add(c2Label)
		
		c3Label = MathTex("Col3",":")
		c3Label.next_to(color3,LEFT)

		color3.add(c3Label)
		color3.next_to(color2,DOWN)

		self.wait(0.5)
		self.play(FadeIn(color1),run_time=2)

		properColor = {i+1 : {'fill_color': ManimColor.from_hsv([item/4,1,255])} for i,item in enumerate(c1)}
		graphProper = Graph(vertices,edges,vertex_config=properColor,layout={1:[0,0,0],2:[3,0,0],3:[6,0,0],4:[1.5,-1.5,0],5:[4.5,-1.5,0]},labels=True).move_to(graph)
		self.play(ReplacementTransform(graph,graphProper),run_time=2)
		self.wait(0.5)
		label1 = MathTex('``Valid\"').next_to(color1,RIGHT)
		self.play(Write(label1))
		self.wait(0.5)

		self.play(color2.animate.next_to(color1,DOWN))
		improperColor = {i+1 : {'fill_color': ManimColor.from_hsv([item/4,1,255])} for i,item in enumerate(c2)}
		graphImproper = Graph(vertices,edges,vertex_config=improperColor,layout={1:[0,0,0],2:[3,0,0],3:[6,0,0],4:[1.5,-1.5,0],5:[4.5,-1.5,0]},edge_config={(1,4):{'stroke_color':RED},(2,3):{'stroke_color':RED}},labels=True).move_to(graph)
		self.wait(0.5)
		
		self.play(ReplacementTransform(graph,graphImproper),run_time=2)
		self.wait(0.5)
		label2 = MathTex('``Invalid\"').next_to(color2,RIGHT)
		self.play(Write(label2))
		self.wait(0.5)
		
		self.play(color3.animate.next_to(color2,DOWN))
		chromaticColor = {i+1 : {'fill_color': ManimColor.from_hsv([item/4,1,255])} for i,item in enumerate(c3)}
		graphChromatic = Graph(vertices,edges,vertex_config=chromaticColor,layout={1:[0,0,0],2:[3,0,0],3:[6,0,0],4:[1.5,-1.5,0],5:[4.5,-1.5,0]},labels=True).move_to(graph)
		self.wait(0.5)

		self.play(Transform(graphImproper,graphChromatic),run_time=2)
		self.wait(0.5)
		label3 = MathTex('``Chromatic\"').next_to(color3,RIGHT)
		self.play(Write(label3))

		self.wait(1)
	
	def getSequence(self,sequence):
		result = VGroup()
		result.add(Text(str(sequence[0]),color=ManimColor.from_hsv([sequence[0]/4,1,255])))
		for i in range(1,len(sequence)):
			result.add(Text(str(sequence[i]),color=ManimColor.from_hsv([sequence[i]/4,1,255])).next_to(result[i-1],RIGHT))

		result.move_to([0,0,0])
		result.add(Brace(result[0],[-1,0,0]))
		result.add(Brace(result[len(result)-2],[1,0,0]))

		return result

class SeqCol(Scene):
	def construct(self):
		vertices = [1,2,3,4,5]
		edges = [(1,2),(1,4),(2,3),(2,4),(2,5),(3,5),(4,5)]
		graph = Graph(vertices,edges,layout={1:[0,0,0],2:[3,0,0],3:[6,0,0],4:[1.5,-1.5,0],5:[4.5,-1.5,0]},labels=True)

		graph.move_to([0,0,0])
		graph.to_edge(UP)

		self.play(FadeIn(graph),run_time=2)
		
		set1Label = MathTex("S_1:")
		set2Label = MathTex("S_2:")
		set3Label = MathTex("S_3:")

		setLabels = VGroup(set1Label,set2Label,set3Label)

		self.play(setLabels.animate.arrange(DOWN))
		self.play(setLabels.animate.to_edge(LEFT))

		arrObj = Array()
		colorSeq = [1,2,1,3,4]
		colors = arrObj.getArray(colorSeq)
		colorsIndices = arrObj.getIndices(colors,1)
		colorsGroup = VGroup(colors,colorsIndices)
		for item in colors:
			item[1].set_opacity(0)
			
		self.play(FadeIn(colorsGroup),run_time=2)

		vertices = [1,2,3,4,5]
		mVertices = self.getSequence(vertices)
		mVertices.next_to(colors,DOWN)
		vLabel = MathTex("Vertices",":=")

		vLabel.next_to(mVertices,LEFT)

		verticesGroup = VGroup(vLabel,mVertices)
		verticesGroup.move_to([0,0,0])
		verticesGroup.move_to([0,-2,0])

		self.play(FadeIn(verticesGroup),run_time=2)

		set1 = []
		set2 = []
		set3 = []
		
		mSet1 = VGroup()
		mSet2 = VGroup()
		mSet3 = VGroup()

		j=0
		while j<len(vertices):
			
			vertex = vertices[j]
			set1.append(vertex)
			mSet1.add(Text(str(vertex)))
			for i in range(len(edges)):
				if edges[i][0]==vertex and edges[i][0] in vertices and edges[i][1] in vertices:
					set2.append(edges[i][1])
					mSet2.add(Text(str(edges[i][1])))
			for i in range(len(vertices)):
				if vertices[i] not in set2 and vertices[i] not in set1:
					set3.append(vertices[i])
					mSet3.add(Text(str(vertices[i])))
			

			mSet1.arrange(RIGHT)
			mSet1.next_to(setLabels[0],RIGHT)
			mSet2.arrange(RIGHT)
			mSet2.next_to(setLabels[1],RIGHT)
			mSet3.arrange(RIGHT)
			mSet3.next_to(setLabels[2],RIGHT)

			self.play(FadeIn(mSet1),FadeIn(mSet2),FadeIn(mSet3),run_time=2)

			index = 0
			for item in set3:
				if (vertex,item) not in edges:
					val = set3.pop(0)
					set1.append(val)

					self.play(mSet3[index].animate.next_to(mSet1[-1],RIGHT),run_time=2)
					index+=1

			while index<len(mSet3):
				val = set3.pop(0)
				set2.append(val)

				self.play(mSet3[index].animate.next_to(mSet2[-1],RIGHT),run_time=2)
				index+=1

			flag = False
			for item in set1:
				vertices.remove(item)
				self.play(colors[item-1][1].animate.set_opacity(1),run_time=2)

				self.play(graph[item].animate.set_color(ManimColor.from_hsv([colorSeq[item-1]/4,1,255])))
				
				self.play(FadeOut(mVertices[item-1]),run_time=2)
				flag = True

			set1=[]
			set2=[]
			set3=[]

			if not flag:
				j+=1

			self.play(FadeOut(mSet1),FadeOut(mSet2),FadeOut(mSet3),run_time=2)
			mSet1 = VGroup()
			mSet2 = VGroup()
			mSet3 = VGroup()


		self.wait(1)
		
	def getSequence(self,sequence):
		result = VGroup()
		result.add(Text(str(sequence[0])))
		for i in range(1,len(sequence)):
			result.add(Text(str(sequence[i])).next_to(result[i-1],RIGHT))

		result.move_to([0,0,0])
		#result.add(Brace(result[0],[-1,0,0]))
		#result.add(Brace(result[len(result)-2],[1,0,0]))

		return result

class DE(Scene):
	def construct(self):
		targetVector = [2,3,5,1,4]
		mTargetVector = self.getArray(targetVector)
		tempVector = [2,0,0,1,0]
		mTempVector = self.getArray(tempVector)
		randomPopulation = [1,5,3,4,2]
		mRandomPopulation = self.getArray(randomPopulation)

		targetLabel = MathTex("Target Vector",":=").next_to(mTargetVector,LEFT)
		tempLabel = MathTex("Temporary Vector",":=").next_to(mTempVector,LEFT)
		randLabel = MathTex("Random Population",":=").next_to(mRandomPopulation,LEFT)
		
		target = VGroup(targetLabel,mTargetVector)
		tempV = VGroup(tempLabel,mTempVector)
		randPop = VGroup(randLabel,mRandomPopulation)

		target.move_to([0,0,0])
		tempV.move_to([0,0,0])
		randPop.move_to([0,0,0])

		allGroup = VGroup(target,tempV,randPop)

		self.play(allGroup.animate.arrange(DOWN),run_time=2)
		self.wait(0.5)

		diff = [5,3,4]
		mDiff = self.getArray(diff)
		diffLabel = MathTex("\\{R.P.\\} - \\{T.V.\\}",":=").next_to(mDiff,LEFT)
		
		diffV = VGroup(diffLabel,mDiff)
		diffV.move_to(allGroup[-1])

		self.play(diffV.animate.next_to(allGroup[-1],DOWN),run_time=2)

		allGroup.add(diffV)
		self.play(allGroup.animate.move_to([0,0,0]),run_time=2)

		mutantVector = [2,5,4,1,3]
		mMutant = self.getArray(mutantVector)
		mutantLabel = MathTex("Mutant Vector",":=").next_to(allGroup,DOWN)
		self.play(FadeIn(mutantLabel),run_time=2)
		
		preMutant = mTempVector.copy()
		preMutant.move_to(allGroup[1])
		self.play(preMutant.animate.next_to(mutantLabel,RIGHT),run_time=2)
		mutantV = VGroup(mutantLabel,preMutant)
		self.play(mutantV.animate.next_to(allGroup,DOWN),run_time=2)
		mMutant.move_to(preMutant)

		self.play(ReplacementTransform(preMutant,mMutant))

		allGroup.add(VGroup(preMutant,mutantLabel,mMutant))

		self.play(allGroup.animate.scale(0.90))
		trialVector = [2,3,5,4,1]
		mTrial = self.getArray(trialVector)
		self.play(allGroup.animate.move_to([0,1,0]),run_time=2)
		trialLabel = MathTex("Trial Vector",":=").scale(0.90).next_to(allGroup,DOWN)
		self.play(FadeIn(trialLabel),run_time=2)

		partial1 = allGroup[0][1][0:3].copy()
		partial2 = allGroup[0][1][3:].copy()

		self.play(partial1.animate.next_to(trialLabel,RIGHT),run_time=2)
		self.play(partial2.animate.next_to(partial1,0.1*RIGHT),run_time=2)

		trialV = VGroup(partial1,partial2,trialLabel)
		self.play(trialV.animate.scale(0.90).next_to(allGroup,DOWN),run_time=2)
		self.play(ReplacementTransform(trialV[1][0][1],Text("4").move_to(trialV[1][0][1]).scale(0.90)),ReplacementTransform(trialV[1][1][1],Text("1").move_to(trialV[1][1][1]).scale(0.90)),run_time=2)

		allGroup.add(trialV)
		self.play(allGroup.animate.move_to([0,0,0]),run_time=2)

		self.wait(1)


	def getArray(self,array):
		resultArray=VGroup()
		resultArray.add(self.getBox(array[0]))

		for i in range(1,len(array)):
			box=self.getBox(array[i])
			box.shift(RIGHT*i)
			resultArray.add(box)
		
		resultArray.move_to((0,0,0))
		
		return resultArray

	def getBox(self,text):
		result=VGroup()

		box=Square(side_length=1,color=GRAY)
		text=Text(str(text)).move_to(box.get_center())

		result.add(box,text)
		return result

class GSA(Scene):
	def construct(self):
		timeT1 = ['Agent',1,2,3,4,5]
		nextTime = ['Agent',5.36,2.14,3.08,1.78,5.96]
		nextTimeDiscrete = ['Agent',2,4,3,5,1]

		mTimeT1 = self.getArray(timeT1)
		timeT1Label = MathTex("P_t",":=").next_to(mTimeT1,LEFT)
		mNextTime = self.getArray(nextTime)
		nextTimeLabel = MathTex("P_{t+1}",":=").next_to(mNextTime,LEFT)
		mNextTimeDiscrete = self.getArray(nextTimeDiscrete)
		nextTimeDiscreteLabel = MathTex("P_{t+1}","(Discrete)",":=").next_to(mNextTimeDiscrete,LEFT)

		t1 = VGroup(mTimeT1,timeT1Label).move_to([0,0,0])
		nextT1 = VGroup(mNextTime,nextTimeLabel)
		nextT1Discrete = VGroup(mNextTimeDiscrete,nextTimeDiscreteLabel)

		for i in range(0,len(t1[0])):
			t1[0][i][1].scale(0.5)
			nextT1[0][i][1].scale(0.5)
			nextT1Discrete[0][i][1].scale(0.5)

		self.play(FadeIn(t1),run_time=2)
		self.wait(0.5)

		#self.play(t1.animate.move_to([0,2,0]),run_time=2)
		allGroup = VGroup(t1)

		self.wait(0.5)
		#self.play(allGroup.animate.move_to([0,0,0]),run_time=2)

		nextT1.move_to(allGroup.get_center())
		self.play(nextT1.animate.next_to(allGroup,DOWN),run_time=2)

		allGroup.add(nextT1)

		#self.play(allGroup.animate.move_to([0,2,0]),run_time=2)
		self.play(allGroup.animate.move_to([0,0,0]),run_time=2)

		nextT1Discrete.move_to(allGroup[1])

		self.play(nextT1Discrete.animate.next_to(allGroup,DOWN),run_time=2)
		allGroup.add(nextT1Discrete)

		self.play(allGroup.animate.move_to([0,0,0]),run_time=2)

		allGroup = VGroup(t1,nextT1,nextT1Discrete)
		#self.play(allGroup.animate.arrange(DOWN))

		self.wait(1)


	def getArray(self,array):
		resultArray=VGroup()
		resultArray.add(self.getBox(array[0]))

		for i in range(1,len(array)):
			box=self.getBox(array[i])
			box.shift(RIGHT*i)
			resultArray.add(box)
		
		resultArray.move_to((0,0,0))
		
		return resultArray

	def getBox(self,text):
		result=VGroup()

		box=Square(side_length=1,color=GRAY)
		text=Text(str(text)).move_to(box.get_center())

		result.add(box,text)
		return result
		
