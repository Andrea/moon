//
// NativeMethods.cs
//
// Author:
//   Miguel de Icaza (miguel@ximian.com)
//   Jackson Harper  (jackson@ximian.com)
//   Rolf Bjarne Kvinge  (RKvinge@novell.com)
//
// Copyright 2007 Novell, Inc.
//
// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:
// 
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
// OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
using Mono;
using System;
using System.Runtime.InteropServices;
using System.Reflection;
using System.Windows;
using System.Windows.Browser;
using System.Windows.Media;
using System.Windows.Controls;
using System.Collections;
using System.ComponentModel;

namespace Moonlight {

	public class Loader {
		Mono.Xaml.XamlLoader rl;
		AppDomain domain;
		
		// [DONE] 1. Load XAML file 
		// 2. Make sure XAML file exposes a few new properites:
		//    a. Loaded  (this is the method to call)
		//    b. x:Class (it specifies the assembly to request from the server, and the class to load).
		// 3. Request the browser to download the files
		// 4. From the assembly, lookup the specified class
		// 5. From the class lookup the specified method
		// 6. Run the method
		// 7. If none of those properties are there, we can return

		public static Loader CreateXamlLoader (IntPtr native_loader, IntPtr plugin, IntPtr surface, string filename, string contents)
		{
			try {
				return new Loader (native_loader, plugin, surface, filename, contents);
			} catch (Exception ex) {
				Console.Error.WriteLine ("Loader::CreateXamlLoader: Unable to create managed xaml loader: {0}", ex.Message);
				return null;
			}
		}
		
		public static void DisposeXamlLoader (Loader loader)
		{
			try {
				loader.Dispose ();
			} catch (Exception ex) {
				Console.Error.WriteLine ("Loader::Dispose: Unable to dispose: {0}.", ex.Message);
			}
		}
		
		public Loader (IntPtr native_loader, IntPtr plugin, IntPtr surface, string filename, string contents)
		{
			domain = Helper.CreateDomain (plugin);

			rl = (Mono.Xaml.XamlLoader) Helper.CreateInstanceAndUnwrap (
				domain, typeof (DependencyObject).Assembly.FullName, 
				"Mono.Xaml.ManagedXamlLoader");

			rl.Setup (native_loader, plugin, surface, filename, contents);
		}
		
		public void Dispose ()
		{
			if (domain != null) {
				Helper.UnloadDomain (domain);
				domain = null;
			}
			rl = null;
			GC.SuppressFinalize (this);
		}
		
		~Loader ()
		{
			Dispose ();
		}
	}

	class Moonlight {
		static int count;
		
		static void Main ()
		{
			Console.WriteLine ("Running Moonlight.cs {0}", count++);
			Console.WriteLine ("mscorlib: {0}", typeof (object).Module.FullyQualifiedName);
			Console.WriteLine ("agclr: {0}", typeof (Canvas).Module.FullyQualifiedName);
			Console.WriteLine ("agmono: {0}", typeof (Helper).Module.FullyQualifiedName);
		}
	}
}
